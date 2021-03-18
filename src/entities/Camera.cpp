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
    mFovHalfAngle(22.5f)
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
            rays.push_back(generateSingleRay({i, j}));
        }
    }
    return rays;
}

Ray Camera::generateSingleRay(const glm::ivec2 &pixelPos)
{
    // Generate coords for the start point of the ray and the and the end point of the ray.
    const float xNormal = static_cast<float>(pixelPos.x) / static_cast<float>(mScreenResolution.x);
    const float yNormal = static_cast<float>(pixelPos.y) / static_cast<float>(mScreenResolution.y);

    // So far, the view frustum is just a cube.
    glm::vec4 nearPlane(xNormal, yNormal, - 1, 1);
    glm::vec4 farPlane(xNormal, yNormal, 1, 1);

    glm::mat4 projectionMat = glm::perspective(
            glm::radians(mFovHalfAngle * 2),
            mAspectRatio,
            0.1f,
            100.f);

    glm::mat4 inverseProjectionMat = glm::inverse(projectionMat);  // This is deadly to performance.

    // Multiply the coords by the inverse perspective mat to give the typical view frustum.
    nearPlane = inverseProjectionMat * nearPlane;
    farPlane = inverseProjectionMat * farPlane;

    // So far, this has happened in left hand space, so we need to go to right handed space.
    nearPlane.z *= -1;
    farPlane.z *= -1;

    nearPlane /= nearPlane.w;
    farPlane /= farPlane.w;

    // Convert from eye space to world space. This uses the inverse view matrix.
    nearPlane += mPosition;     // THIS IS WRONG
    farPlane += mPosition;      // THIS IS WRONG (you need to apply a rotation as well.)


    // Convert to ray format where we have an origin and then a direction
    return {
            nearPlane,
            glm::normalize(farPlane - nearPlane)
    };
}

