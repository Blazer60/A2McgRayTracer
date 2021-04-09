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

/**
 * Used to normalise a value between a range. There are no bound checks
 * for value x. Additionally, lB and uB do not have to be the correct way
 * round. However, this may not yield the desired effect.
 * @param x The value you want to interpolate
 * @param lB The lowest value x can be.
 * @param uB The highest value x can be.
 * @return A value between [0, 1] inclusive.
 */
float normalise(const float &x, const float &lB, const float &uB);

/**
 * Maps the value x from [xLb, xUb] -> [yLb, yUb] (inclusive). A value of x
 * out of x bounds specified, will result in a value outside the y bounds
 * specified. yLb and yUb do not have to be in increasing order if you would
 * like the output to be flipped.
 * @see normalise()
 * @param x The value you want to interpolate
 * @param xLb The lowest value x can be.
 * @param xUb The highest value x can be.
 * @param yLb The lowest value y can be.
 * @param yUb The highest value y can be.
 * @return A value between [yLb, yUb] inclusive.
 */
float map(const float &x, const float &xLb, const float &xUb, const float &yLb, const float &yUb);


#endif //A2MCGRAYTRACER_GEOMETRY_H
