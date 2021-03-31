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
         const actorLightingMaterial &material, vertex *vertices) :
         Actor(mPosition, eulerRotation, mScale, material),
         mVertices{vertices[0], vertices[1], vertices[2]}
{
    transformVertices();  // for safety.

    glm::vec3 ab = mVertices[1].position - mVertices[0].position;
    glm::vec3 ac = mVertices[2].position - mVertices[0].position;
    mSurfaceNormal = glm::normalize(glm::cross(ab, ac));
}

void Tri::transformVertices()
{
    glm::mat4 translationMat = glm::translate(mPosition);
    glm::mat4 rotMat = glm::toMat4(mRotation);
    glm::mat4 scaleMat = glm::scale(mScale);

    glm::mat4 transform =  translationMat * rotMat * scaleMat;


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

    const float scalarToP = glm::dot((v0->globalPosition - ray.mPosition), mSurfaceNormal) / (dot);
    if (scalarToP <= 0.f) { return { false }; }  // The ray went the opposite direction.

    const glm::vec3 point = ray.mPosition + scalarToP * ray.mDirection;

    // Point in triangle
    const float sideApHeight = point.y - v0->globalPosition.y;

    float w1 = (v0->globalPosition.x * mSideAc.y - point.x * mSideAc.y + sideApHeight * mSideAc.x) / mW1Denominator;
    float w2;
    if (mSideAc.y != 0.f)
    {
        w2 = (sideApHeight - w1 * mSideAb.y) / mSideAc.y;
    }
    else
    {
        // A and C are vertically aligned so we can just normalise for w2.
        w2 = normalise(point.x, mVertices[0].globalPosition.x, mVertices[1].globalPosition.x);
    }


    if (w1 <= 0.f || w2 <= 0.f || w1 + w2 >= 1) { return { false }; } // Our point lies out side of the triangle.

    // We've hit the triangle
    return {
        true,
        point,
        mSurfaceNormal,
        mMaterial
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
    mSideAb = mVertices[1].globalPosition - mVertices[0].globalPosition;
    mSideAc = mVertices[2].globalPosition - mVertices[0].globalPosition;
    mW1Denominator = mSideAb.y * mSideAc.x - mSideAb.x * mSideAc.y;
}
