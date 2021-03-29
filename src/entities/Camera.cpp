/**
 * @file Camera.cpp.cc
 * @brief Allows the ray tracer to perceive the world through the camera's perspective. Only one camera can be the main
 * camera. However, multiple camera's can exist in world space at once.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */

#include <iostream>
#include "Camera.h"

Camera::Camera(const glm::vec3 &mPosition, const glm::vec3 &eulerAngle, const glm::vec3 &mScale,
               const glm::ivec2 &mScreenResolution, const float &mFovHalfAngle) :
               Entity(mPosition, eulerAngle, mScale),
               mScreenResolution(mScreenResolution),
               mAspectRatio(static_cast<float>(mScreenResolution.x) / static_cast<float>(mScreenResolution.y)),
               mFovHalfAngle(mFovHalfAngle)
{
    init();
}

Camera::Camera(const glm::ivec2 &mScreenResolution) : Entity(),
    mScreenResolution(mScreenResolution),
    mAspectRatio(static_cast<float>(mScreenResolution.x) / static_cast<float>(mScreenResolution.y)),
    mFovHalfAngle(22.5f)
{
    init();
}

void Camera::init()
{
    mInvProjectionMat = glm::perspective(
            glm::radians(mFovHalfAngle * 2),
            mAspectRatio,
            0.1f,
            100.f);

    mInvProjectionMat = glm::inverse(mInvProjectionMat);  // This is deadly to performance.
}

void Camera::update(float deltaTime)
{
    updateMat();
}

void Camera::updateMat()
{
    // Convert from eye space to world space. This uses the inverse view matrix.
    mRotationMat = glm::toMat4(mRotation);
    mTranslationMat = glm::translate(mPosition);

    // Multiply the coords by the inverse perspective mat to give the typical view frustum.
    mInvPrtMat = mTranslationMat * mRotationMat * mInvProjectionMat;
}

std::vector<Ray> Camera::generateRays()
{
    std::vector<Ray> rays;
    for (int j = 0; j < mScreenResolution.y; ++j)
    {
        for (int i = 0; i < mScreenResolution.x; ++i)
        {
            rays.push_back(generateSingleRay({i, j}));  // TODO: could be the wrong way round??
        }
    }
    return rays;
}

Ray Camera::generateSingleRay(const glm::ivec2 &pixelPos)
{
    // Generate coords for the start point of the ray and the and the end point of the ray.
    const float xNormal = map(static_cast<float>(pixelPos.x),
                              0.f, static_cast<float>(mScreenResolution.x),
                              -1.f, 1.f);
    const float yNormal = map(static_cast<float>(pixelPos.y),
                              0.f, static_cast<float>(mScreenResolution.y),
                              1.f, -1.f);

    // So far, the view frustum is just a cube.
    glm::vec4 nearPlane(xNormal, yNormal, - 1, 1);
    glm::vec4 farPlane(xNormal, yNormal, 1, 1);

    // Multiply the coords by the inverse perspective mat to give the typical view frustum.
    // We also multiply be the transform and rotation mat.
    nearPlane = mInvPrtMat * nearPlane;
    farPlane = mInvPrtMat * farPlane;

    // So far, this has happened in left hand space, so we need to go to right handed space.
    nearPlane.z *= -1;
    farPlane.z *= -1;

    // Normalise the vector coords by their w component.
    nearPlane /= nearPlane.w;
    farPlane /= farPlane.w;

    // Convert to ray format where we have an origin and then a direction
    return {
            nearPlane,
            glm::normalize(farPlane - nearPlane),
            glm::vec3(1.f)
    };
}

