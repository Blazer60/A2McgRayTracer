/**
 * @file Tri.h
 * @brief Holds three vertices that are related to one another.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 31/03/2021
 */


#ifndef A2MCGRAYTRACER_TRI_H
#define A2MCGRAYTRACER_TRI_H

#include "Actor.h"
#include "Ray.h"
#include "Geometry.h"

#include "glm.hpp"
#include "glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"
#include "GLM/vec3.hpp"

struct vertex
{
    glm::vec3 position;
    glm::vec3 globalPosition;

    explicit vertex(const glm::vec3 &position) : position(position)
    {}
};

/**
 * Holds three vertices that are related to one another.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 31/03/2021]
 */
class Tri : public Actor
{
public:
    Tri(const glm::vec3 &mPosition, const glm::vec3 &eulerRotation, const glm::vec3 &mScale,
        const actorLightingMaterial &material, vertex *vertices);

    hitInfo isIntersecting(const Ray &ray) override;

    bool quickIsIntersecting(const Ray &ray) override;

    void update(float deltaTime) override;

protected:
    vertex mVertices[3];
    glm::vec3 mSurfaceNormal;

    void transformVertices();

private:
    // Lengths use for is intersecting function.
    glm::vec3 mSideAc;
    glm::vec3 mSideAb;

    float mW1Denominator{};

    void constructCollisionEdges();
};


#endif //A2MCGRAYTRACER_TRI_H
