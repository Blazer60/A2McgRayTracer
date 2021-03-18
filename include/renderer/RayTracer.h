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
    RayTracer() = default;

    void update();
    void render();

protected:
    std::shared_ptr<Camera> mMainCamera;
    std::vector<Entity*> mEntities;
    std::vector<Actor*> mPhysicalObjects;


};


#endif //A2MCGRAYTRACER_RAYTRACER_H
