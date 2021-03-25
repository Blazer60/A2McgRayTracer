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

Sphere::Sphere(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale, const glm::vec3 &colour,
               float mRadius)
               : Actor(mPosition, mRotation, mScale, colour),
               mRadius(mRadius), mIsBobbing(true)
{
    mStaticPos = mPosition;
    mTime = 0;
    mAmplitude = 1;
    mFrequency = 1;
}

Sphere::Sphere() : Actor(), mRadius(5), mIsBobbing(true)
{
    mStaticPos = glm::vec3(0);
}

hitInfo Sphere::isIntersecting(Ray ray)
{
    glm::vec3 delta = mPosition - ray.mPosition;
    float deltaDot = glm::dot(delta, ray.mDirection);  // Gives us the

    const float closestPoint = glm::length(delta - (deltaDot * ray.mDirection));

    // The ray did not intersect so we don't need to calculate the colour, position and hit normal.
    if (closestPoint > mRadius) { return { false, {}, {}, {} }; }

    // Work out the position that the ray intercepted the sphere.
    const float x = glm::sqrt(mRadius * mRadius - closestPoint * closestPoint);
    glm::vec3 hitPosition = ray.mPosition + (deltaDot - x) * ray.mDirection;

    // Ray hit normal
    glm::vec3 hitNormal = glm::normalize(hitPosition - mPosition);

    // Crude working out of the lighting.
    float intensity = glm::dot(hitNormal, -ray.mDirection);
    glm::vec3 colour = mColour * intensity;

    return {
            true,
            hitPosition,
            colour,
            hitNormal
    };
//    hitInfo hit = raySphereIntersection(ray, mPosition, mRadius);
//    // Work out the colour depending on the hit normal.
//    if (hit.hit)
//    {
//        float intensity = glm::dot(hit.hitNormal, -ray.mDirection);
//        hit.colour = mColour * intensity;
//    }
//    return hit;
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
    std::cout << mPosition.x << ", " << mPosition.y << ", " << mPosition.z << std::endl;
}
