/**
 * @file Ray.cpp.cc
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#include "Ray.h"

Ray::Ray(const glm::vec3 &mPosition, const glm::vec3 &mDirection, const glm::vec3 &energy)
        : mPosition(mPosition), mDirection(mDirection), mEnergy(energy)
{}
