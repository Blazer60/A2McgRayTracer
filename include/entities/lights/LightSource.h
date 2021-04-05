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

    /** Directional Light */
    LightSource(const glm::vec3 &direction, const glm::vec3 &colour);

    /** Point Light */
    LightSource(const glm::vec3 &position, const glm::vec3 &colour, const float &fallOff);

    ~LightSource() override = default;

    void update(float deltaTime) override {};

    /**
     * Constructs a Ray object that can be casted in the world.
     * @param pos
     * @return
     */
    Ray getRayToLight(glm::vec3 pos);

    /**
     * Determines the intensity of light that reaches a position.
     * @param pos
     * @return
     */
    lightingMaterial getInfo(glm::vec3 pos);

    enum mTypes { Directional, Point };
    int mType;

protected:
    lightingMaterial mMaterial;
    bool mIsFarAway;

    // Directional light
    glm::vec3 mDirection;

    // Point light
    float mFallOffConstant;
};


#endif //A2MCGRAYTRACER_LIGHTSOURCE_H
