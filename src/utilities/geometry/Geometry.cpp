/**
 * @file Geometry.cpp.c
 * @brief Procedural functions that handle miscellaneous
 * geometry and intersections between them.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 22/03/2021
 */


#include "Geometry.h"

glm::vec3 getClosestPoint(const Ray &ray, const glm::vec3 &point)
{
    glm::vec3 delta = point - ray.mPosition;  // This is used in multiple places.
    glm::vec3 distanceOnRay = glm::dot(delta, ray.mDirection) * ray.mDirection;
    return delta - distanceOnRay;
}

hitInfo raySphereIntersection(const Ray &ray, const glm::vec3 &point, const float &radius)
{
    glm::vec3 delta = point - ray.mPosition;
    float deltaDot = glm::dot(delta, ray.mDirection);  // Gives us the

    const float closestPoint = glm::length(delta - (deltaDot * ray.mDirection));

    // The ray did not intersect so we don't need to calculate the colour, position and hit normal.
    if (closestPoint > radius) { return { false, {}, {}, {} }; }

    // Work out the position that the ray intercepted the sphere.
    const float x = glm::sqrt(radius * radius - closestPoint * closestPoint);
    glm::vec3 hitPosition = ray.mPosition + (deltaDot - x) * ray.mDirection;

    // Ray hit normal
    glm::vec3 hitNormal = glm::normalize(hitPosition - point);

    return {
        true,
        hitPosition,
        {},
        hitNormal
    };
}

float normalise(const float &x, const float &lB, const float &uB)
{
    return (x - lB) / (uB - lB);
}

float map(const float &x, const float &xLb, const float &xUb, const float &yLb, const float &yUb)
{
    const float xN = normalise(x, xLb, xUb);
    return yLb + xN * (yUb - yLb);
}
