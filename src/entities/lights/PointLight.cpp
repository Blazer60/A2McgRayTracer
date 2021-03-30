/**
 * @file PointLight.cpp.cc
 * @brief A single point in space the emits light in all directions.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 30/03/2021
 */


#include "PointLight.h"

PointLight::PointLight() :
    LightSource(),
    mFallOffConstant(1)
{}

PointLight::PointLight(const glm::vec3 &pos, const glm::vec3 &colour, const float &intensity, const float &fallOff) :
    LightSource(pos, colour, intensity),
    mFallOffConstant(fallOff)
{}

Ray PointLight::getRayToLight(glm::vec3 pos)
{
    glm::vec3 direction = glm::normalize( mPosition - pos);
    return {
        pos,
        direction,
        glm::vec3(0)
    };
}

lightingMaterial PointLight::getInfo(glm::vec3 pos)
{
    glm::vec3 d = mPosition - pos;
    float dDot = glm::dot(d, d);
    glm::vec3 q = glm::vec3(mFallOffConstant * 1 / dDot);
    return {
        mMaterial.baseColour,
        mMaterial.ambientIntensity,
        mMaterial.diffuseIntensity * q,
        mMaterial.specularIntensity * q
    };
}
