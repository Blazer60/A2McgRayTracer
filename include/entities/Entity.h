/**
 * @file Entity.h
 * @brief An entity is an object the can live in world space.
 * NOTE: Not all entities can be seen by the camera. @see Actors.h
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 17/03/2021
 */


#ifndef A2MCGRAYTRACER_ENTITY_H
#define A2MCGRAYTRACER_ENTITY_H

#include "glm.hpp"

/**
 * An entity is an object the can live in world space.
 * NOTE: Not all entities can be seen by the camera. @see Actors.h
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 17/03/2021]
 */
class Entity
{
protected:
    glm::vec3 mPosition;
    glm::vec3 mRotation;  // The will need to change.
    glm::vec3 mScale;
public:
    Entity();
    Entity(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale);

    virtual void update(float deltaTime) = 0;

    const glm::vec3 &getPosition() const
    {
        return mPosition;
    }
};


#endif //A2MCGRAYTRACER_ENTITY_H
