/**
 * @file Camera.cpp.cc
 * @brief Allows the ray tracer to perceive the world through the camera's perspective. Only one camera can be the main
 * camera. However, multiple camera's can exist in world space at once.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#include "Camera.h"

Camera::Camera(const glm::vec3 &mPosition, const glm::vec3 &mRotation, const glm::vec3 &mScale,
               const glm::ivec2 &mScreenResolution, float mAspectRatio, float mFovHalfAngle) :
               Entity(mPosition, mRotation, mScale),
               mScreenResolution(mScreenResolution),
               mAspectRatio(mAspectRatio),
               mFovHalfAngle(mFovHalfAngle)
{}

Camera::Camera(const glm::ivec2 &mScreenResolution) : Entity(),
    mScreenResolution(mScreenResolution),
    mAspectRatio(static_cast<float>(mScreenResolution.x) / static_cast<float>(mScreenResolution.y)),
    mFovHalfAngle(45.f)
{}

void Camera::update(float deltaTime)
{

}

std::vector<Ray> Camera::generateRays()
{
    std::vector<Ray> rays(mScreenResolution.x * mScreenResolution.y);
    for (int i = 0; i < mScreenResolution.x; ++i)
    {
        for (int j = 0; j < mScreenResolution.y; ++j)
        {
            rays.push_back(generateSingleRay(i, j));
        }
    }
    return rays;
}

Ray Camera::generateSingleRay(const int &x, const int &y)
{
    return {};
}

