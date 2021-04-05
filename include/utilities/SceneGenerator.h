/**
 * @file SceneGenerator.h
 * @brief A function for loading specific scenes for the Ray Tracer
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 01/04/2021
 */


#ifndef A2MCGRAYTRACER_SCENEGENERATOR_H
#define A2MCGRAYTRACER_SCENEGENERATOR_H

#include "Entity.h"
#include "LightSource.h"
#include "Camera.h"
#include "Actor.h"
#include "Sphere.h"
#include "Tri.h"

namespace lvl
{
    enum sceneName
    {
        /** A highly reflective mirror-like sphere on top of a white plane made of two triangles. */
        TheDefaultScene,

        /** A RGB Triangle sat on a white plane. */
        Triangle,

        MirrorRoom,

        NumberOfScenes
    };
}

struct scene
{
    bool                        success;
    Camera                      *mainCamera;
    std::vector<Entity*>        entities;
    std::vector<Camera*>        cameras;
    std::vector<Actor*>         actors;
    std::vector<LightSource*>   lights;
};

scene loadScene(const glm::ivec2 &screenSize, unsigned int index=0);

#endif //A2MCGRAYTRACER_SCENEGENERATOR_H
