/**
 * @file Geometry.h
 * @brief Procedural functions that handle miscellaneous
 * geometry and intersections between them.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 22/03/2021
 */


#ifndef A2MCGRAYTRACER_GEOMETRY_H
#define A2MCGRAYTRACER_GEOMETRY_H

#include "Ray.h"

#include "glm.hpp"

glm::vec3 getClosestPoint(const Ray &ray, const glm::vec3 &point);
hitInfo raySphereIntersection(const Ray &ray, const glm::vec3 &point, const float &radius);

float normalise(const float &x, const float &lB, const float &uB);
float map(const float &x, const float &xLb, const float &xUb, const float &yLb, const float &yUb);


#endif //A2MCGRAYTRACER_GEOMETRY_H
