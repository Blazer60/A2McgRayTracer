/**
 * @file Sphere.cpp.cc
 * @brief A mathematical sphere that can bob up and down in place.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#include <iostream>
#include "Sphere.h"

Sphere::Sphere() : Actor(), mRadius(5), mIsBobbing(false)
{
    init();
}

Sphere::Sphere(const glm::vec3 &position, const actorLightingMaterial &lightingMaterial, const float &radius) :
    Actor(position, lightingMaterial),
    mRadius(radius),
    mIsBobbing(false)
{
    init();
}

hitInfo Sphere::isIntersecting(const Ray &ray)
{
    glm::vec3 delta = mPosition - ray.mPosition;
    float deltaDot = glm::dot(delta, ray.mDirection);

    if (deltaDot < 0) { return { false, {}, {}, {} }; }  // The ray went backward so we won't hit anything

    const float closestPoint = glm::length(delta - (deltaDot * ray.mDirection));

    // The ray did not intersect so we don't need to calculate the colours, position and hit normal.
    if (closestPoint > mRadius) { return { false, {}, {}, {} }; }

    // Work out the position that the ray intercepted the sphere.
    const float x = glm::sqrt(mRadius * mRadius - closestPoint * closestPoint);
    glm::vec3 hitPosition = ray.mPosition + (deltaDot - x) * ray.mDirection;

    // Ray hit normal
    glm::vec3 hitNormal = glm::normalize(hitPosition - mPosition);

    return {
            true,
            hitPosition,
            hitNormal,
            mMaterial
    };
}

bool Sphere::quickIsIntersecting(const Ray &ray)
{
    // The same as isIntersecting, but we don't need to work out all the other information.
    glm::vec3 delta = mPosition - ray.mPosition;
    float deltaDot = glm::dot(delta, ray.mDirection);

    if (deltaDot < 0) { return false; }  // The ray went backward so we won't hit anything

    const float closestPoint = glm::length(delta - (deltaDot * ray.mDirection));

    // The ray did not intersect so we don't need to calculate the colours, position and hit normal.
    if (closestPoint > mRadius) { return false; }

    return true;
}

void Sphere::update(float deltaTime)
{
    if (mIsBobbing)
    {
        const auto tau = glm::two_pi<float>();
        mTime += deltaTime;
        if (mTime > tau)  // We've loops through an entire circle
        {
            mTime -= tau;  // Reduce the number so that we don't tend to infinity
        }

        float offSet = glm::sin(mTime * mFrequency) * mAmplitude;
        mPosition.y = mStaticPos.y + offSet;
    }
}

void Sphere::init()
{
    mStaticPos = mPosition;
    mTime = 0;
    mAmplitude = 1;
    mFrequency = 1;
}
