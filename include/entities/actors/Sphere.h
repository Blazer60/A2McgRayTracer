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
#include "Geometry.h"

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

    Sphere(const glm::vec3 &position, const actorLightingMaterial &lightingMaterial, const float &radius);

    ~Sphere() override = default;

    void update(float deltaTime) override;
    hitInfo isIntersecting(const Ray &ray) override;

    bool quickIsIntersecting(const Ray &ray) override;

protected:
    float mRadius;

private:
    void init();

    // The following attributes allow the ball to go up and down following a sine wave.
    const bool mIsBobbing;  // Make the Sphere bob up and down in place.
    glm::vec3 mStaticPos;  // Track where the ball's original position was.
    float mTime{};
    float mAmplitude{};
    float mFrequency{};
};


#endif //A2MCGRAYTRACER_SPHERE_H
