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
#include "Sphere.h"

#include "glm.hpp"

glm::vec3 getClosestPoint(const Ray &ray, const glm::vec3 &point);
glm::vec3 raySphereIntersection(const Ray &ray, const Sphere &sphere);

#endif //A2MCGRAYTRACER_GEOMETRY_H
