/**
 * @file RayTracer.h
 * @brief The renderer that displays the world to the screen.
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
#include <iostream>

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
    void updateAndHold();  // Unused.

protected:
    void event();
    void update();
    void render();

    /**
     * Changes the items in the world to the specified scene requested by either index or by name
     * (in enum lvl::[TheNameOfTheScene]). Throws an error if no such scene exists.
     * @see SceneGenerator.h
     * @param index The number of name (enum) of scene that you want to load.
     */
    void changeScene(unsigned int index);

    /**
     * Tracers an "origin" ray into world space until all
     * energy is lost or the ray reaches the max bounce limit.
     * @param originRay
     * @return A colour for the specified ray.
     */
    glm::vec3 trace(Ray &originRay);

    /**
     * Casts shadow rays to each light source in the scene.
     * Additionally, it reflects the ray depending of the surface it hit.
     * @param hitInfo
     * @return The colour of an object at the hit position.
     */
    glm::vec3 traceShadows(Ray &ray, const hitInfo &hit);

    /**
     * Traces a ray towards a light source.
     * @param ray A ray towards said light source
     * @param lightSource The light source you're targeting.
     * @return True if it managed to get clear line of sight to the light source.
     */
    bool traceToLightSource(const Ray &ray, const LightSource *lightSource);

    /**
     * Reflects the ray based on the surface it hit.
     * @param ray The ray that you want to modify.
     * @param hit The surface that the ray hit.
     */
    static void reflectRay(Ray &ray, const hitInfo &hit);

    /**
     * Gets the closest object to the ray's origin.
     * If no object was hit, the default diffuse is the 'skybox'.
     * @param ray
     * @return Information about what was hit.
     */
    hitInfo getHitInWorld(const Ray &ray);

    /**
     * Same as getHitInWorld but only returns if there was a hit or not.
     * It will immediately exit upon finding a hit.
     * @param ray
     * @return True if it hit an object.
     */
    bool quickGetHitInWorld(const Ray &ray);

    /***
     * Returns a colour of the 'skybox' based the on the direction of a ray.
     * @param rayDirection
     * @return
     */
    glm::vec3 sampleSkybox(glm::vec3 rayDirection);

    /** The Camera in which the Rays are generated from. */
    Camera *mMainCamera {};

    /** All entities within the world. Cameras, Actors, lights, etc. */
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

    // Channels
    bool mShowAmbient;
    bool mShowDiffuse;
    bool mShowSpecular;
    bool mShowSkybox;

    /** The bounce limit the program is at for the current frame */
    int mBounceLimit{ 1 };

    /** The absolute bounce limit the program can go to. */
    int mMaxBounceLimit{ 5 };

    // Information & user input
    unsigned int mFrameCount{ 0 };
    bool mIsRunning{ true };
    unsigned int mCurrentScene{ 999 };
};


#endif //A2MCGRAYTRACER_RAYTRACER_H
