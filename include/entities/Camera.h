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
#include "Geometry.h"
#include "Ray.h"

#include "glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"
#include "GLM/vec3.hpp"

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
    explicit Camera(const glm::ivec2 &screenResolution);
    Camera(const glm::vec3 &position, const glm::vec3 &eulerAngle, const glm::vec3 &scale,
           const glm::ivec2 &screenResolution, const float &fovHalfAngle);

    ~Camera() override = default;

    void update(float deltaTime) override;
    void updateMat();

    /** Creates a ray based on the pixel position on the screen and the matrix transform of the camera. */
    Ray generateSingleRay(const glm::ivec2 &pixelPos);

protected:
    const glm::ivec2 mScreenResolution;
    const float mAspectRatio;
    const float mFovYHalfAngle;

private:
    glm::mat4 mRotationMat;
    glm::mat4 mTranslationMat;
    glm::mat4 mInvProjectionMat;

    /** Rotation mat, translation mat and inverse projection mat all in one. */
    glm::mat4 mInvPrtMat;

    /** Generates the InvProjectionMat on creation */
    void init();
};


#endif //A2MCGRAYTRACER_CAMERA_H
