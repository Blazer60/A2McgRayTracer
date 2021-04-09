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

float normalise(const float &x, const float &lB, const float &uB)
{
    return (x - lB) / (uB - lB);
}

float map(const float &x, const float &xLb, const float &xUb, const float &yLb, const float &yUb)
{
    const float xN = normalise(x, xLb, xUb);
    return yLb + xN * (yUb - yLb);
}
