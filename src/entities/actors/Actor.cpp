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
             const actorLightingMaterial &material) :
             Entity(mPosition, eulerRotation, mScale),
             mMaterial(material)
{}

Actor::Actor(const glm::vec3 &position, const actorLightingMaterial &lightingMaterial) :
    Entity(position, glm::vec3(0.f), glm::vec3(1.f)),
    mMaterial(lightingMaterial)
{}

Actor::Actor() : Entity(), mMaterial()
{}
