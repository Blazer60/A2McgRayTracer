/**
 * @file Camera.h
 * @brief Allows the ray tracer to perceive the world through the camera's perspective. Only one camera can be the main
 * camera. However, multiple camera's can exist in world space at once.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#ifndef A2MCGRAYTRACER_CAMERA_H
#define A2MCGRAYTRACER_CAMERA_H

#include "Entity.h"
#include "glm.hpp"
#include <Ray.h>

#include <vector>


/**
 * Allows the ray tracer to perceive the world through the camera's perspective. Only one camera can be the main
 * camera. However, multiple camera's can exist in world space at once.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
class Camera : public Entity
{
public:
    explicit Camera(const glm::ivec2 &mScreenResolution);
    Camera(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale,
           const glm::ivec2 &mScreenResolution, float mAspectRatio, float mFovHalfAngle);

    void update(float deltaTime) override;

    std::vector<Ray> generateRays();

protected:
    glm::ivec2 mScreenResolution;
    float mAspectRatio;
    float mFovHalfAngle;
private:
    Ray generateSingleRay(const int &x, const int &y);
};


#endif //A2MCGRAYTRACER_CAMERA_H
