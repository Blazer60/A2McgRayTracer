/**
 * @file Entity.cpp.cc
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 17/03/2021
 */

#include "Entity.h"


Entity::Entity(const glm::vec3 &position, const glm::vec3 &eulerRotation, const glm::vec3 &mScale) :
    mPosition(position),
    mRotation(eulerRotation),
    mScale(mScale)
{}

Entity::Entity() :
    mPosition(0),
    mRotation(glm::vec3(0)),
    mScale(1)
{}
