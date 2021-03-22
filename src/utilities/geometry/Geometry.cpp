/**
 * @file Geometry.cpp.c
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 22/03/2021
 */


#include "Geometry.h"

glm::vec3 getClosestPoint(const Ray &ray, const glm::vec3 &point)
{
    glm::vec3 delta = point - ray.mPosition;  // This is used in multiple places.
    glm::vec3 distanceOnRay = glm::dot((delta), ray.mDirection) * ray.mDirection;
    return delta - distanceOnRay;
}
