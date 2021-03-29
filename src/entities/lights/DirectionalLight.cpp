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
    LightSource(glm::vec3(0),
                glm::vec3(-0.785, 0, 0),
                glm::vec3(0),
                glm::vec3(1),
                1),
    mIntensityColour(1),
    mDirection(glm::vec3(0.f, -0.707f, -0.707f))
{

}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 colour, float intensity) :
        LightSource(glm::vec3(0),
                    glm::vec3(0),
                    glm::vec3(1),
                    colour,
                    intensity),
        mIntensityColour(colour * intensity),
        mDirection(glm::normalize(direction))
{

}

Ray DirectionalLight::getRayToLight(glm::vec3 pos)
{
    return {
        pos,
        mDirection,
        glm::vec3(0.f)
    };
}

lightInfo DirectionalLight::getInfo(glm::vec3 pos)
{
    return {
        mDirection,
        mIntensityColour
    };
}


