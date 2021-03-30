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

LightSource::LightSource() :
    Entity(),
    mMaterial(glm::vec3(1.f))
{}

LightSource::LightSource(const glm::vec3 &position, const glm::vec3 &colour,
                         float intensity) :
                         Entity(position, glm::vec3(0), glm::vec3(1)),
                         mMaterial(colour * intensity)
{}

LightSource::LightSource(const glm::vec3 &colour, const float &intensity) :
    Entity(),
    mMaterial(glm::vec3(colour * intensity))
{}
