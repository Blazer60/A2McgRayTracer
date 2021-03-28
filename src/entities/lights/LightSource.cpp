/**
 * @file LightSource.cpp.cc
 * @brief A light source that can live in world space. The source cannot
 * be seen in world space nor do lens flares appear.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 28/03/2021
 */


#include "LightSource.h"

LightSource::LightSource() : mColour(1), mIntensity(1) {}

LightSource::LightSource(const glm::vec3 &position, const glm::vec3 &eulerRotation, const glm::vec3 &mScale,
                         const glm::vec3 &mColour, float mIntensity) : Entity(position, eulerRotation, mScale),
                                                                       mColour(mColour), mIntensity(mIntensity)
{}
