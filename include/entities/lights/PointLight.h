/**
 * @file PointLight.h
 * @brief A single point in space the emits light in all directions.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 30/03/2021
 */


#ifndef A2MCGRAYTRACER_POINTLIGHT_H
#define A2MCGRAYTRACER_POINTLIGHT_H

#include "LightSource.h"

/**
 * A single point in space the emits light in all directions.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 30/03/2021]
 */
class PointLight : public LightSource
{
public:
    PointLight();
    PointLight(const glm::vec3 &pos, const glm::vec3 &colour, const float &intensity, const float &fallOff=1);

    Ray getRayToLight(glm::vec3 pos) override;

    lightingMaterial getInfo(glm::vec3 pos) override;

protected:
    /**
     * Controls the rate at which the light intensity falls off. 0 - Falls of immediately, 1 - Falls of per m^2
     */
    float mFallOffConstant;
};


#endif //A2MCGRAYTRACER_POINTLIGHT_H
