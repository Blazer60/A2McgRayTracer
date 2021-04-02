/**
 * @file Tri.cpp.cc
 * @brief Holds three vertices that are related to one another.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 31/03/2021
 */

#include "Tri.h"

Tri::Tri(const glm::vec3 &mPosition, const glm::vec3 &eulerRotation, const glm::vec3 &mScale,
         const actorLightingMaterial &material, vertex *vertices, bool useVertexMat) :
         Actor(mPosition, eulerRotation, mScale, material),
         mVertices{vertices[0], vertices[1], vertices[2]},
         mUseVertexMaterial(useVertexMat)
{
    glm::vec3 ab = mVertices[1].position - mVertices[0].position;
    glm::vec3 ac = mVertices[2].position - mVertices[0].position;
    mSurfaceNormal = glm::normalize(glm::cross(ab, ac));

    transformVertices();  // for safety.
}

void Tri::transformVertices()
{
    glm::mat4 translationMat = glm::translate(mPosition);
    glm::mat4 rotMat = glm::toMat4(mRotation);
    glm::mat4 scaleMat = glm::scale(mScale);

    glm::mat4 transform = translationMat * rotMat * scaleMat;


    for (auto &vertex : mVertices)
    {
        vertex.globalPosition = transform * glm::vec4(vertex.position, 1);
    }
    constructCollisionEdges();
}

hitInfo Tri::isIntersecting(const Ray &ray)
{
    if (mW1Denominator == 0.f) { return { false }; }  // Degenerate triangle case.

    const vertex *v0 = mVertices;  // Gets the first vertex in the array

    // Ray plane intersection
    const float dot = glm::dot(ray.mDirection, mSurfaceNormal);
    if (dot == 0) { return { false }; }  // We are parallel with the triangle.

    const float scalarToP = glm::dot(v0->globalPosition - ray.mPosition, mSurfaceNormal) / (dot);
    if (scalarToP <= 0.f) { return { false }; }  // The ray went the opposite direction.
    //if (dot >= 0) { return { false }; }  // We are looking at the back of the triangle

    const glm::vec3 point = ray.mPosition + scalarToP * ray.mDirection;

    // Point in triangle
    const float s5 = mUseXz ? point.z - v0->globalPosition.z : point.y - v0->globalPosition.y;

    float w1 = (v0->globalPosition.x * s1 + s5 * s2 - point.x - s1) / mW1Denominator;
    float w2;
    if (s1 != 0.f)
    {
        w2 = (s5 - w1 * s3) / s1;
    }
    else
    {
        // A and C are vertically aligned so we can just normalise for w2.
        w2 = normalise(point.x, mVertices[0].globalPosition.x, mVertices[2].globalPosition.x);
    }


    if (w1 <= 0.f || w2 <= 0.f || w1 + w2 >= 1) { return { false }; } // Our point lies out side of the triangle.

    // We've hit the triangle

    if (!mUseVertexMaterial)
    {
        return {  // Use the base material provided by the tri
                true,
                point,
                mSurfaceNormal,
                mMaterial
        };
    }

    // lerp between the different materials at each vertex
    actorLightingMaterial abLerp = mix(mVertices[0].material, mVertices[1].material, w1);
    actorLightingMaterial abcLerp = mix(abLerp, mVertices[2].material, w2);
    return {
            true,
            point,
            mSurfaceNormal,
            abcLerp
    };
}

bool Tri::quickIsIntersecting(const Ray &ray)
{
    return isIntersecting(ray).hit;  // There isn't anything we can optimise
}

void Tri::update(float deltaTime)
{
    transformVertices();
}

void Tri::constructCollisionEdges()
{
    mUseXz =    mSurfaceNormal == glm::vec3(0.f, 1.f, 0.f)
                || mSurfaceNormal == glm::vec3(0.f, -1.f, 0.f);
    if (mUseXz)
    {
        // The Triangle is lying flat, so we'll use x and z instead.
        s1 = mVertices[2].globalPosition.z - mVertices[0].globalPosition.z;
        s2 = mVertices[2].globalPosition.x - mVertices[0].globalPosition.x;
        s3 = mVertices[1].globalPosition.z - mVertices[0].globalPosition.z;
        s4 = mVertices[1].globalPosition.x - mVertices[0].globalPosition.x;
    }
    else
    {
        s1 = mVertices[2].globalPosition.y - mVertices[0].globalPosition.y;
        s2 = mVertices[2].globalPosition.x - mVertices[0].globalPosition.x;
        s3 = mVertices[1].globalPosition.y - mVertices[0].globalPosition.y;
        s4 = mVertices[1].globalPosition.x - mVertices[0].globalPosition.x;
    }

    mW1Denominator = (s3 * s2) - (s4 * s1);
}

actorLightingMaterial Tri::mix(const actorLightingMaterial &mat1, const actorLightingMaterial &mat2, const float &alpha)
{
    const glm::vec3 alphaVec = glm::vec3(alpha);
    return {
        glm::mix(mat1.baseColour, mat2.baseColour, alphaVec),
        glm::mix(mat1.ambientIntensity, mat2.ambientIntensity, alphaVec),
        glm::mix(mat1.diffuseIntensity, mat2.diffuseIntensity, alphaVec),
        glm::mix(mat1.specularIntensity, mat2.specularIntensity, alphaVec),
        glm::mix(mat1.transmissionIntensity, mat2.transmissionIntensity, alphaVec),
        glm::mix(mat1.reflectivityIntensity, mat2.transmissionIntensity, alphaVec),
        glm::mix(mat1.shininessConstant, mat2.shininessConstant, alpha)
    };
}
