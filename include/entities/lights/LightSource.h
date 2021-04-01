/**
 * @file LightSource.h
 * @brief A light source that can live in world space. The source cannot
 * be seen in world space nor do lens flares appear.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 28/03/2021
 */


#ifndef A2MCGRAYTRACER_LIGHTSOURCE_H
#define A2MCGRAYTRACER_LIGHTSOURCE_H

#include "Entity.h"
#include "Ray.h"
#include "LightingMaterials.h"

#include "glm.hpp"

/**
 * Information returned by a light source upon request.
 */
struct lightInfo
{
    glm::vec3 direction;
    glm::vec3 colour;
};


/**
 * A light source that can live in world space. The source cannot
 * be seen in world space nor do lens flares appear.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 28/03/2021]
 */
class LightSource : public Entity
{
public:
    LightSource();

    LightSource(const glm::vec3 &position, const glm::vec3 &mColour, float mIntensity);

    LightSource(const glm::vec3 &colour, const float &intensity);

    ~LightSource() override = default;

    void update(float deltaTime) override {};

    /**
     * Constructs a Ray object that can be casted in the world.
     * @param pos
     * @return
     */
    virtual Ray getRayToLight(glm::vec3 pos) = 0;

    /**
     * Determines the intensity of light that reaches a position.
     * @param pos
     * @return
     */
    virtual lightingMaterial getInfo(glm::vec3 pos) = 0;

protected:
    lightingMaterial mMaterial;
};


#endif //A2MCGRAYTRACER_LIGHTSOURCE_H
