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
        auto *light = new LightSource(glm::vec3(1.f, 1.f, 1.f),glm::vec3(1));
        level.lights.push_back(light);
        level.entities.push_back(light);

        // Ball
        actorLightingMaterial metallic(glm::vec3(0.f),
                                      glm::vec3(1.f),
                                      glm::vec3(0.8f),
                                      50.f);

        auto *ball = new Sphere({ 0.f, 1.f, 0.f },
                                 metallic,
                                 1.f);
        level.actors.push_back(ball);
        level.entities.push_back(ball);

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
        auto *light = new LightSource(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1));
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
                                  verts, true);
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


    /**
     * A mirror room that contains a single red ball and a point light.
     * NOTE: high bounce limit is needed to make an amazing room.
     * @param screenSize
     */
    scene level3(const glm::ivec2 &screenSize)
    {
        scene level { true };

        // Create the main camera
        level.mainCamera = new Camera({ 4.5f, -1.5f, 4.5f },
                                      { -0.3f, 0.785f, 0.f },
                                      { 1.f, 1.f, 1.f },
                                      screenSize,
                                      22.5
        );
        level.cameras.push_back(level.mainCamera);
        level.entities.push_back(level.mainCamera);

        auto *pointLight = new LightSource({0.f, 4.5f, 0.f},
                                           { 0.961f, 0.933f, 0.725f },
                                          75);
        level.lights.push_back(pointLight);
        level.entities.push_back(pointLight);


        actorLightingMaterial white(glm::vec3(0.58f, 0.f, 0.f),
                                    glm::vec3(0.1),
                                    glm::vec3(0.1f),
                                    64.f);

        auto *centerBall = new Sphere({0.f, -4.f, 0.f}, white, 1.f);
        level.actors.push_back(centerBall);
        level.entities.push_back(centerBall);

        actorLightingMaterial metallic(glm::vec3(0.f),
                                       glm::vec3(1.f),
                                       glm::vec3(0.8f),
                                       50.f);

        actorLightingMaterial grey(glm::vec3(0.5f),
                                   glm::vec3(0.1f),
                                   glm::vec3(0.f),
                                   64.f);

        // Flooring
        vertex cube[8] = {
                vertex({ -1.f, 1.f, -1.f }),    // Top-back-left [0]
                vertex({ -1.f, 1.f, 1.f }),     // Top-front-left [1]
                vertex({ 1.f, 1.f, 1.f }),      // Top-front-right [2]
                vertex({ 1.f, 1.f, -1.f }),     // Top-back-right [3]

                vertex({ -1.f, -1.f, -1.f }),   // Bottom-back-left [4]
                vertex({ -1.f, -1.f, 1.f }),    // Bottom-front-left [5]
                vertex({ 1.f, -1.f, 1.f }),     // Bottom-front-right [6]
                vertex({ 1.f, -1.f, -1.f })     // Bottom-back-right [7]
        };

        glm::vec3 cubeScale(5.f);

        // Bottom Side
        vertex a[3] = { cube[7], cube[4], cube[5] };
        auto *floorLeft = new Tri(glm::vec3(0.f),
                                  glm::vec3(0.f),
                                  cubeScale,
                                  grey, a);
        level.actors.push_back(floorLeft);
        level.entities.push_back(floorLeft);

        vertex b[3] = { cube[5], cube[6], cube[7] };
        auto *floorRight = new Tri(glm::vec3(0.f),
                                   glm::vec3(0.f),
                                   cubeScale,
                                   grey, b);
        level.actors.push_back(floorRight);
        level.entities.push_back(floorRight);

        // Left Side
        vertex c[3] = { cube[4], cube[0], cube[5] };
        auto *leftBottom = new Tri(glm::vec3(0.f),
                                   glm::vec3(0.f),
                                   cubeScale,
                                   metallic, c);
        level.actors.push_back(leftBottom);
        level.entities.push_back(leftBottom);

        vertex d[3] = { cube[0], cube[1], cube[5] };
        auto *leftTop = new Tri(glm::vec3(0.f),
                                glm::vec3(0.f),
                                cubeScale,
                                metallic, d);
        level.actors.push_back(leftTop);
        level.entities.push_back(leftTop);

        // Front Side
        vertex e[3] = { cube[5], cube[2], cube[6] };
        auto *frontBottom = new Tri(glm::vec3(0.f),
                                glm::vec3(0.f),
                                    cubeScale,
                                    metallic, e);
        level.actors.push_back(frontBottom);
        level.entities.push_back(frontBottom);

        vertex f[3] = { cube[1], cube[2], cube[6] };
        auto *frontTop = new Tri(glm::vec3(0.f),
                                glm::vec3(0.f),
                                 cubeScale,
                                 metallic, f);
        level.actors.push_back(frontTop);
        level.entities.push_back(frontTop);

        // Back side
        vertex g[3] = { cube[4], cube[3], cube[7] };
        auto *backBottom = new Tri(glm::vec3(0.f),
                                glm::vec3(0.f),
                                   cubeScale,
                                   metallic, g);
        level.actors.push_back(backBottom);
        level.entities.push_back(backBottom);

        vertex h[3] = { cube[0], cube[3], cube[7] };
        auto *backTop = new Tri(glm::vec3(0.f),
                                   glm::vec3(0.f),
                                cubeScale,
                                metallic, h);
        level.actors.push_back(backTop);
        level.entities.push_back(backTop);

        // Right side
        vertex i[3] = { cube[2], cube[6], cube[7] };
        auto *rightBottom = new Tri(glm::vec3(0.f),
                                    glm::vec3(0.f),
                                    cubeScale,
                                    metallic, i);
        level.actors.push_back(rightBottom);
        level.entities.push_back(rightBottom);

        vertex j[3] = { cube[3], cube[6], cube[7] };
        auto *rightTop = new Tri(glm::vec3(0.f),
                                    glm::vec3(0.f),
                                 cubeScale,
                                 metallic, j);
        level.actors.push_back(rightTop);
        level.entities.push_back(rightTop);

        // Top side
        vertex k[3] = { cube[1], cube[2], cube[3] };
        auto *topRight = new Tri(glm::vec3(0.f),
                                 glm::vec3(0.f),
                                 cubeScale,
                                 metallic, k);
        level.actors.push_back(topRight);
        level.entities.push_back(topRight);

        vertex l[3] = { cube[0], cube[1], cube[3] };
        auto *topLeft = new Tri(glm::vec3(0.f),
                                glm::vec3(0.f),
                                cubeScale,
                                metallic, l);
        level.actors.push_back(topLeft);
        level.entities.push_back(topLeft);


        return level;
    }
}

scene loadScene(const glm::ivec2 &screenSize, unsigned int index)
{
    if (index > lvl::NumberOfScenes) { return { false }; }  // No scene exist with given index.
    switch (index)
    {
        case 0:
        default:
            return scenes::level1(screenSize);
        case 1:
            return scenes::level2(screenSize);
        case 2:
            return scenes::level3(screenSize);
    }
}
