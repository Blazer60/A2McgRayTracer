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
    actorLightingMaterial material;

    explicit vertex(const glm::vec3 &position) : position(position)
    {}

    vertex(const glm::vec3 &position, const actorLightingMaterial &lightingMaterial) :
    position(position), material(lightingMaterial)
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
        const actorLightingMaterial &material, vertex *vertices, bool useVertexMat=false);

    ~Tri() override = default;

    hitInfo isIntersecting(const Ray &ray) override;

    bool quickIsIntersecting(const Ray &ray) override;

    void update(float deltaTime) override;

protected:
    vertex mVertices[3];
    glm::vec3 mSurfaceNormal;

    void transformVertices();
    bool mUseVertexMaterial;

    // coord pair used when calculating point in triangle. Defaults to x-y
    enum mUseCoordPair { Xy, Xz, Yz };
    int mOrientation{ Xy };

    // Lengths used for is intersecting function.
    float s1, s2, s3, s4;
    float mW1Denominator;

    void constructCollisionEdges();

    /** Mixes between mat1 and mat2 by alpha. */
    static actorLightingMaterial mix(const actorLightingMaterial &mat1,
                                     const actorLightingMaterial &mat2,
                                     const float &alpha);
};


#endif //A2MCGRAYTRACER_TRI_H
