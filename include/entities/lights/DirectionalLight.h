/**
 * @file DirectionalLight.h
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 28/03/2021
 */


#ifndef A2MCGRAYTRACER_DIRECTIONALLIGHT_H
#define A2MCGRAYTRACER_DIRECTIONALLIGHT_H

#include "LightSource.h"

/**
 * A directional light source that is considered to be infinitely far away
 * (such as the sun).
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 28/03/2021]
 */
class DirectionalLight : public LightSource
{
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 direction, glm::vec3 colour, float intensity);

    Ray getRayToLight(glm::vec3 pos) override;

    lightInfo getInfo(glm::vec3 pos) override;

protected:
    glm::vec3 mIntensityColour;
    glm::vec3 mDirection;
};


#endif //A2MCGRAYTRACER_DIRECTIONALLIGHT_H
