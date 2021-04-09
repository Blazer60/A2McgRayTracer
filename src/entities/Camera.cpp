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

Camera::Camera(const glm::vec3 &position, const glm::vec3 &eulerAngle, const glm::vec3 &scale,
               const glm::ivec2 &screenResolution, const float &fovHalfAngle) :
               Entity(position, eulerAngle, scale),
               mScreenResolution(screenResolution),
               mAspectRatio(static_cast<float>(screenResolution.x) / static_cast<float>(screenResolution.y)),
               mFovYHalfAngle(fovHalfAngle)
{
    init();
}

Camera::Camera(const glm::ivec2 &screenResolution) :
    Entity(),
    mScreenResolution(screenResolution),
    mAspectRatio(static_cast<float>(screenResolution.x) / static_cast<float>(screenResolution.y)),
    mFovYHalfAngle(22.5f)
{
    init();
}

void Camera::init()
{
    mInvProjectionMat = glm::perspective(
            glm::radians(mFovYHalfAngle * 2),
            mAspectRatio,
            0.1f,
            100.f);

    mInvProjectionMat = glm::inverse(mInvProjectionMat);
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

    mInvPrtMat = mTranslationMat * mRotationMat * mInvProjectionMat;
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

