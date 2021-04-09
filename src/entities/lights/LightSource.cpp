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

// Directional Light source
LightSource::LightSource(const glm::vec3 &direction, const glm::vec3 &colour) :
    Entity(), mType(Directional), mDirection(glm::normalize(direction)), mMaterial(colour), mFallOffConstant(0.f)
{}

// Point Light source
LightSource::LightSource(const glm::vec3 &position, const glm::vec3 &colour, const float &fallOff) :
    Entity(position, glm::vec3(0.f), glm::vec3(1.f)), mType(Point),
    mDirection(0.f), mMaterial(colour), mFallOffConstant(fallOff)
{}

Ray LightSource::getRayToLight(glm::vec3 pos)
{
    switch (mType)
    {
        case Point:
            return { pos, glm::normalize( mPosition - pos) };
        case Directional:
        default:
            return { pos, mDirection };
    }
}

lightingMaterial LightSource::getInfo(glm::vec3 pos)
{
    switch (mType)
    {
        case Point:
        {
            // Inverse square law.
            glm::vec3 d = mPosition - pos;
            float dDot = glm::dot(d, d);
            glm::vec3 q = glm::vec3(mFallOffConstant / dDot);
            return {
                    mMaterial.baseColour,
                    mMaterial.ambientIntensity,
                    mMaterial.diffuseIntensity * q,
                    mMaterial.specularIntensity * q
            };
        }
        default:
            return mMaterial;
    }
}
