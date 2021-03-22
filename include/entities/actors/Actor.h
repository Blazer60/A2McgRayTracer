/**
 * @file Actor.h
 * @brief An object in world space that can be seen by the camera.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#ifndef A2MCGRAYTRACER_ACTOR_H
#define A2MCGRAYTRACER_ACTOR_H

#include "Entity.h"
#include "glm.hpp"
#include "Ray.h"

/**
 * An object in world space that can be seen by the camera.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
class Actor : public Entity
{
public:
    /**
     * Actors by default are set to pink.
     */
    Actor();

    Actor(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale, const glm::vec3 &colour);

    virtual hitInfo isIntersecting(Ray ray) = 0;

    const glm::vec3 &getColour() const
    {
        return mColour;
    }

protected:
    glm::vec3 mColour;  // defined here as hitInfo requires a colour to return.
};


#endif //A2MCGRAYTRACER_ACTOR_H
