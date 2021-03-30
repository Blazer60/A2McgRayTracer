/**
 * @file DirectionalLight.cpp.cc
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 28/03/2021
 */


#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() :
    LightSource(),
    mDirection(glm::vec3(0.f, -0.707f, -0.707f))
{}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 colour, float intensity) :
        LightSource(colour, intensity),
        mDirection(glm::normalize(direction))
{}

Ray DirectionalLight::getRayToLight(glm::vec3 pos)
{
    return {
        pos,
        mDirection,
        glm::vec3(0.f)  // Stops accidental reflection ray being made.
    };
}

lightingMaterial DirectionalLight::getInfo(glm::vec3 pos)
{
    return mMaterial;
}


