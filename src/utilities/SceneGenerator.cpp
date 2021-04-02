/**
 * @file SceneGenerator.cpp.c
 * @brief A function for loading specific scenes for the Ray Tracer
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 01/04/2021
 */


#include "SceneGenerator.h"

namespace scenes
{
    scene level1(const glm::ivec2 &screenSize)
    {
        scene level { true };

        // Create the main camera
        level.mainCamera = new Camera({ 0.f, 1.5f, 6.f },
                                      { 0.f, 0.f, 0.f },
                                      { 1.f, 1.f, 1.f },
                                      screenSize,
                                      22.5
                                      );
        level.cameras.push_back(level.mainCamera);
        level.entities.push_back(level.mainCamera);

        // Lighting
        auto *light = new DirectionalLight(glm::vec3(1.f, 1.f, 1.f),
                                           glm::vec3(1),
                                           1.f);
        level.lights.push_back(light);
        level.entities.push_back(light);

        // Ball
        actorLightingMaterial metallic(glm::vec3(0.f),
                                      glm::vec3(1.f),
                                      glm::vec3(0.8f),
                                      50.f);

        auto *ball2 = new Sphere({ 0.f, 1.f, 0.f },
                                 metallic,
                                 1.f);
        level.actors.push_back(ball2);
        level.entities.push_back(ball2);

        // Floor
        actorLightingMaterial white(glm::vec3(0.9f),
                                    glm::vec3(0.1),
                                    glm::vec3(0.1f),
                                    50.f);

        vertex vert[3] = {
                vertex({ 0.f, 0.f, 0.f }),
                vertex({ 0.f, 0.f, 1.f }),
                vertex({ 1.f, 0.f, 0.f })
        };
        auto *floor1 = new Tri(glm::vec3(-20.f, 0.f, -20.f),
                               glm::vec3(0.f),
                               { 40.f, 1.f, 40.f },
                               white,
                               vert);
        level.actors.push_back(floor1);
        level.entities.push_back(floor1);

        vertex vert2[3] = {
                vertex({ 1.f, 0.f, 1.f }),
                vertex({ 1.f, 0.f, 0.f }),
                vertex({ 0.f, 0.f, 1.f }),
        };
        auto *floor2 = new Tri({ -20.f, 0.f, -20.f },
                               { 0.f, 0.f, 0.f },
                               { 40.f, 1.f, 40.f },
                               white,
                               vert2);
        level.actors.push_back(floor2);
        level.entities.push_back(floor2);


        return level;
    }
}

scene loadScene(const glm::ivec2 &screenSize, unsigned int index)
{
    if (index > sceneName::NumberOfScenes) { return { false }; }  // No scene exist with given index.
    switch (index)
    {
        case 0:
        default:
            return scenes::level1(screenSize);
    }
}
