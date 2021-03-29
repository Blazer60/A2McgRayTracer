/**
 * @file Actor.cpp.c
 * @brief An object in world space that can be seen by the camera.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */
 
#include "Actor.h"

Actor::Actor(const glm::vec3 &mPosition, const glm::vec3 &eulerRotation, const glm::vec3 &mScale,
             const glm::vec3 &colour,
             const glm::vec3 &specular)
        : Entity(mPosition, eulerRotation, mScale), mAmbient(colour * 0.1f), mDiffuse(colour), mSpecular(specular)
{}

Actor::Actor() : Entity(), mAmbient(0.f, 0.1f, 0.036f), mDiffuse(0.f, 1.f, 0.36f),
    mSpecular(0) {}
