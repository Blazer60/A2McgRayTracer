/**
 * @file Sphere.cpp.cc
 * @brief A mathematical sphere that can bob up and down in place.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#include "Sphere.h"

Sphere::Sphere(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale, const glm::vec3 &colour,
               float mRadius)
               : Actor(mPosition, mRotation, mScale, colour),
               mRadius(mRadius), mIsBobbing(false)
{
    mStaticPos = mPosition;
    mTime = 0;
    mAmplitude = 1;
    mFrequency = 1;
}

Sphere::Sphere() : Actor(), mRadius(5), mIsBobbing(false)
{
    mStaticPos = glm::vec3(0);
}

hitInfo Sphere::isIntersecting(Ray ray)
{
    hitInfo hit = raySphereIntersection(ray, mPosition, mRadius);
    if (hit.hit) { hit.colour = mColour; }
    return hit;
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
