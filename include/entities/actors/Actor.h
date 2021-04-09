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
#include "Ray.h"
#include "LightingMaterials.h"

#include "glm.hpp"
/**
 * An object in world space that can be seen by the camera.
 * Actors by default are set to pink.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
class Actor : public Entity
{
public:
    Actor();

    Actor(const glm::vec3 &position, const actorLightingMaterial &lightingMaterial);

    Actor(const glm::vec3 &position, const glm::vec3 &eulerRotation, const glm::vec3 &scale,
          const actorLightingMaterial &material);

    ~Actor() override = default;

    virtual hitInfo isIntersecting(const Ray &ray) = 0;
    virtual bool quickIsIntersecting(const Ray &ray) = 0;

protected:
    actorLightingMaterial mMaterial;
};


#endif //A2MCGRAYTRACER_ACTOR_H
