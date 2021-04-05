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
#include "Tri.h"
#include "Entity.h"
#include "LightSource.h"
#include "SceneGenerator.h"

#include "MCG_GFX_Lib.h"
#include "SDL.h"


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

    void changeScene(unsigned int index);

    void run();
    void updateAndHold();
    void event();
    void update();
    void render();

protected:
    /**
     * Tracers an "origin" ray into world space.
     * @param ray
     * @return The diffuse intensity from the ray.
     */
    glm::vec3 trace(Ray &ray);

    /**
     * Casts shadow rays to each light source in the scene.
     * @param hitInfo
     * @return
     */
    glm::vec3 traceShadows(Ray &ray, hitInfo &hit);

    /**
     * Gets the closest object to the ray's origin.
     * If no object was hit, the default diffuse is the 'skybox'.
     * @param ray
     * @return Information about what was hit.
     */
    hitInfo getHitInWorld(const Ray &ray);

    bool quickGetHitInWorld(const Ray &ray);



    /// The Camera in which the Rays are generated from.
    Camera *mMainCamera{};
    std::vector<Entity*> mEntities;
    std::vector<Actor*> mActors;
    std::vector<LightSource*> mLights;
    glm::ivec2 mWindowSize;

    // Skybox Colours.

    /** The colour of the ground below the horizon */
    glm::vec3 mGroundColour { 0.408f, 0.380f, 0.357f };

    /** The colour of the horizon */
    glm::vec3 mHorizonColour { 0.482f, 0.937f, 0.976f };

    /** The colour of the sky towards the bottom. */
    glm::vec3 mSkyBottomColour { 0.008f, 0.725f, 1.f };

    /** The colour of the sky when looking directly up */
    glm::vec3 mSkyTopColour { 0.f, 0.059f, 0.486f };

    const float mSkyBottomAngle { 0.08f };

    glm::vec3 sampleSkybox(glm::vec3 rayDirection);

    // Channels
    bool mShowAmbient;
    bool mShowDiffuse;
    bool mShowSpecular;
    bool mShowSkybox;

    int mBounceLimit{ 1 };
    int mMaxBounceLimit{ 5 };

    // Information & user input
    unsigned int mFrameCount{ 0 };
    bool mIsRunning{ true };
    unsigned int mCurrentScene{ 999 };
};


#endif //A2MCGRAYTRACER_RAYTRACER_H
