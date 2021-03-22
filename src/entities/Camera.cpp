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

Camera::Camera(const glm::vec3 &mPosition, const glm::vec3 &eulerAngle, const glm::vec3 &mScale,
               const glm::ivec2 &mScreenResolution, const float &mFovHalfAngle) :
               Entity(mPosition, eulerAngle, mScale),
               mScreenResolution(mScreenResolution),
               mAspectRatio(static_cast<float>(mScreenResolution.x) / static_cast<float>(mScreenResolution.y)),
               mFovHalfAngle(mFovHalfAngle)
{

}

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
    std::vector<Ray> rays;
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
    const float xNormal = map(static_cast<float>(pixelPos.x),
                              0.f, static_cast<float>(mScreenResolution.x),
                              -1.f, 1.f);
    const float yNormal = map(static_cast<float>(pixelPos.y),
                              0.f, static_cast<float>(mScreenResolution.y),
                              -1.f, 1.f);
//    const float xNormal = static_cast<float>(pixelPos.x) / static_cast<float>(mScreenResolution.x);
//    const float yNormal = static_cast<float>(pixelPos.y) / static_cast<float>(mScreenResolution.y);

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
    glm::mat4 rotationMatrix = glm::toMat4(-mRotation);
    glm::mat4 translationMatrix = glm::translate(-mPosition);

    nearPlane = translationMatrix * rotationMatrix * nearPlane;
    farPlane = translationMatrix * rotationMatrix * farPlane;


    // Convert to ray format where we have an origin and then a direction
    return {
            nearPlane,
            glm::normalize(farPlane - nearPlane)
    };
}

