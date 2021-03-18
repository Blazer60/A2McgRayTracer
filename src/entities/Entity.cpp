/**
 * @file Entity.cpp.cc
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 17/03/2021
 */

#include "Entity.h"


Entity::Entity(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale) :
    mPosition(mPosition),
    mRotation(mRotation),
    mScale(mScale)
{}

Entity::Entity() :
    mPosition(0),
    mRotation(0),
    mScale(0)
{}
