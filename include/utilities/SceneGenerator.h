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
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Camera.h"
#include "Actor.h"
#include "Sphere.h"
#include "Tri.h"

enum sceneName
{
    TheDefaultScene,
    NumberOfScenes
};

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
