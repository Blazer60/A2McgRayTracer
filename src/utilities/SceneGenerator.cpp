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
    /**
     * A highly reflective mirror-like sphere on
     * top of a white plane made of two triangles.
     * @param screenSize
     */
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


    /**
     * A RGB Triangle sat on a white plane.
     * @param screenSize
     * @return
     */
    scene level2(const glm::ivec2 &screenSize)
    {
        scene level { true };
        // Create the main camera
        level.mainCamera = new Camera({ 2.f, 1.f, 2.f },
                                      { -0.05f, 0.79f, 0.f },
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

        actorLightingMaterial red({ 1.f, 0.f, 0.f },
                                  glm::vec3(1.f),
                                  glm::vec3(0.f),
                                  10.f);

        actorLightingMaterial green({ 0.f, 1.f, 0.f },
                                    glm::vec3(0.f),
                                    glm::vec3(0.f),
                                    0.f);

        actorLightingMaterial blue({ 0.f, 0.f, 1.f },
                                   glm::vec3(0.f),
                                   glm::vec3(0.f),
                                   0.f);

        vertex verts[3] = {
                vertex({ 0.f, 0.577f, 0.f }, red),
                vertex({ -0.5f, -0.289f, 0.f }, green),
                vertex({ 0.5f, -0.289f, 0.f }, blue)
        };

        auto *triangle = new Tri( { 0.f, 0.3f, 0.f },
                                  glm::vec3(0.f),
                                  glm::vec3(1.f),
                                  red,
                                  verts,
                                  true,
                                  false);
        level.actors.push_back(triangle);
        level.entities.push_back(triangle);

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
        auto *floor1 = new Tri(glm::vec3(-5.f, 0.f, -20.f),
                               glm::vec3(0.f),
                               { 10.f, 1.f, 40.f },
                               white,
                               vert);
        level.actors.push_back(floor1);
        level.entities.push_back(floor1);

        vertex vert2[3] = {
                vertex({ 1.f, 0.f, 1.f }),
                vertex({ 1.f, 0.f, 0.f }),
                vertex({ 0.f, 0.f, 1.f }),
        };
        auto *floor2 = new Tri({ -5.f, 0.f, -20.f },
                               { 0.f, 0.f, 0.f },
                               { 10.f, 1.f, 40.f },
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
        case 1:
            return scenes::level2(screenSize);
    }
}
