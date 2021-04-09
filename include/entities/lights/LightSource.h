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
 * A light source that can live in world space. The source cannot
 * be seen in world space nor do lens flares appear.
 * @paragraph Both Point light and Directional lights stored within
 * Light Source since there is not much difference between the two.
 * If more light types are added in the future, Light Source may have to be split up.
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

    /** Constructs a Ray object that can be casted in the world. */
    Ray getRayToLight(glm::vec3 pos);

    /** Determines the intensity of light that reaches a position. */
    lightingMaterial getInfo(glm::vec3 pos);

    enum mTypes { Directional, Point };
    int mType;

protected:
    lightingMaterial mMaterial;

    // Info for Directional light.
    glm::vec3 mDirection;

    // Info for Point light.
    float mFallOffConstant;
};


#endif //A2MCGRAYTRACER_LIGHTSOURCE_H
