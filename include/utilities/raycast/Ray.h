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

#include "glm.hpp"



/**
 * Holds information about a ray vector in world space.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
class Ray
{
public:
    glm::vec3 mPosition;
    glm::vec3 mDirection;
    glm::vec3 mEnergy;

    Ray() = default;
    Ray(const glm::vec3 &mPosition, const glm::vec3 &mDirection, const glm::vec3 &energy);
};

/**
 * Hit information for when a ray has collided with an object in world space.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
struct hitInfo
{
    bool hit;
    glm::vec3 hitPosition;
    glm::vec3 hitNormal;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif //A2MCGRAYTRACER_RAY_H
