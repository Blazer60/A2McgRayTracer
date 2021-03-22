/**
 * @file Sphere.h
 * @brief A mathematical sphere that can bob up and down in place.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#ifndef A2MCGRAYTRACER_SPHERE_H
#define A2MCGRAYTRACER_SPHERE_H

#include "Actor.h"
#include "glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

/**
 * A mathematical sphere that can bob up and down in place.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
class Sphere : public Actor
{
public:
    Sphere();
    Sphere(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale, const glm::vec3 &colour,
           float mRadius);

    void update(float deltaTime) override;
    hitInfo isIntersecting(Ray ray) override;

    float getRadius() const
    {
        return mRadius;
    }

protected:
    float mRadius;

private:
    const bool mIsBobbing;  // Make the Sphere bob up and down in place.
    glm::vec3 mStaticPos;
    float mTime;
    float mAmplitude;
    float mFrequency;
};


#endif //A2MCGRAYTRACER_SPHERE_H
