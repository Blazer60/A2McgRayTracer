/**
 * @file Ray.h
 * @brief Allows a ray to be constructed and fired into the world.
 * The Ray class will provide information about a ray cast while the
 * hitInfo struct will provide detail about the point of interception.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#ifndef A2MCGRAYTRACER_RAY_H
#define A2MCGRAYTRACER_RAY_H

#include "LightingMaterials.h"

#include "glm.hpp"


/**
 * Holds information about a ray vector in world space.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
class Ray
{
public:
    /** A position vector to where the ray typically starts. */
    glm::vec3 mPosition;

    /** The direction in which the line 'points'. The should always be a Unit Vector */
    glm::vec3 mDirection;

    /** How much energy is left in the ray when it bounces of a surface. Used for calculating the colour */
    glm::vec3 mEnergy;

    Ray() = default;
    Ray(const glm::vec3 &mPosition, const glm::vec3 &mDirection, const glm::vec3 &energy=glm::vec3(0));
};

/**
 * Hit information for when a ray has collided with an object in world space.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
struct hitInfo
{
    /** Did it actually hit a surface? */
    bool hit;

    /** Where it hit the surface. */
    glm::vec3 hitPosition;

    /** The normal to the surface it hit (or orthogonal to the surface). */
    glm::vec3 hitNormal;

    /** The lighting information of the surface to calculate the lighting later on. */
    actorLightingMaterial material;
};

#endif //A2MCGRAYTRACER_RAY_H
