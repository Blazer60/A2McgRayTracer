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
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"

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

    /**
     * The rotation is store as a quat but will typically be set
     * through euler angles as it simpler to wrap our heads around.
     */
    glm::quat mRotation;
    glm::vec3 mScale;
public:
    Entity();
    Entity(const glm::vec3 &position, const glm::vec3 &eulerRotation, const glm::vec3 &mScale);

    virtual void update(float deltaTime) = 0;

    const glm::vec3 &getPosition() const
    {
        return mPosition;
    }
};


#endif //A2MCGRAYTRACER_ENTITY_H
