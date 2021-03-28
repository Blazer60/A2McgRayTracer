/**
 * @file RayTracer.h
 * @brief The renderer the displays the world to the screen.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */


#ifndef A2MCGRAYTRACER_RAYTRACER_H
#define A2MCGRAYTRACER_RAYTRACER_H

#include "Camera.h"
#include "Sphere.h"
#include "Entity.h"
#include "DirectionalLight.h"

#include "MCG_GFX_Lib.h"

#include <memory>
#include <vector>

/**
 * The renderer the displays the world to the screen.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 18/03/2021]
 */
class RayTracer
{
public:
    explicit RayTracer(const glm::ivec2 &mWindowSize);

    void run();
    void updateAndHold();
    void update();
    void render();

protected:
    /// The Camera in which the Rays are generated from.
    Camera *mMainCamera;
    std::vector<Entity*> mEntities;
    std::vector<Actor*> mPhysicalObjects;
    std::vector<LightSource*> mLights;
    glm::ivec2 mWindowSize;
    std::vector<glm::vec3> mPixelBuffer;

    /**
     * Tracers an "origin" ray into world space.
     * @param ray
     * @return The colour intensity from the ray.
     */
    glm::vec3 trace(const Ray &ray);

    /**
     * Casts shadow rays to each light source in the scene.
     * @param hitInfo
     * @return
     */
    glm::vec3 traceShadows(hitInfo &hit);

    /**
     * Gets the closest object to the ray's origin.
     * If no object was hit, the default colour is black.
     * @param ray
     * @return Information about what was hit.
     */
    hitInfo getHitInWorld(const Ray &ray);
};


#endif //A2MCGRAYTRACER_RAYTRACER_H
