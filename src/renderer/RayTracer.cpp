/**
 * @file RayTracer.cpp.cc
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */

#include <iostream>
#include "RayTracer.h"

RayTracer::RayTracer(const glm::ivec2 &mWindowSize) :
    mWindowSize(mWindowSize),
    mPixelBuffer(mWindowSize.x * mWindowSize.y)
{
    if(!mcg::init(mWindowSize)) { throw std::exception(); }

    // Create some entities so that we can if things have worked.
    mMainCamera = new Camera({0.f, 0.f, 0.f},
                             {0.f, 0.f, 0.f},
                             {1.f, 1.f, 1.f},
                             mWindowSize,
                             22.5f);
    mEntities.push_back(mMainCamera);

    // Adding Actors
    auto *s = new Sphere({-1.f, 0.f, 6.f},
                         {0.f, 0.f, 0.f},
                         {1.f, 1.f, 1.f},
                         {0.f, 0.7f, 0.7f},
                         1.f);

    mPhysicalObjects.push_back(s);
    mEntities.push_back(s);

    auto *s1 = new Sphere({1.f, 0.f, 6.f},
                          {0.f, 0.f, 0.f},
                          {1.f, 1.f, 1.f},
                          {0.8f, 0.6f, 0.8f},
                          1.f);

    mPhysicalObjects.push_back(s1);
    mEntities.push_back(s1);

    // Adding lights
    auto *l = new DirectionalLight(glm::vec3(0.f, 0.f, -1.f), glm::vec3(1), 1);
    mLights.push_back(l);
    mEntities.push_back(l);
}

void RayTracer::update()
{
    for (auto &entity : mEntities)
    {
        entity->update(0.1f);
    }
}

void RayTracer::render()
{
    // Loop through each pixel coord pair on the screen.
    for (int y = 0; y < mWindowSize.y; ++y)
    {
        for (int x = 0; x < mWindowSize.x; ++x)
        {
            glm::ivec2 pixelPosition(x, y);
            // Create a ray from our camera
            Ray ray = mMainCamera->generateSingleRay(pixelPosition);

            // Cast it into the world to get our colour.
            glm::vec3 colour = trace(ray);

            // Draw the pixel to MCG pixel buffer.
            mcg::drawPixel(pixelPosition, colour);
        }
    }
}

void RayTracer::updateAndHold()
{
    update();
    render();
    mcg::showAndHold();
}

void RayTracer::run()
{
    while (mcg::processFrame())
    {
        update();
        render();
        std::cout << "Frame out" << std::endl;
    }
}

glm::vec3 RayTracer::trace(Ray &ray)
{
    glm::vec3 colour(0);
    for (int i = 0; i < 2; ++i)
    {
        hitInfo hit = getHitInWorld(ray);

        colour += ray.mEnergy * traceShadows(ray, hit);  // Trace shadow will also reflect the ray
        if (glm::dot(ray.mEnergy, ray.mEnergy) < 0.f)
        {
            break;
        }
    }
    return colour;
}

glm::vec3 RayTracer::traceShadows(Ray &ray, hitInfo &hit)
{
    if (!hit.hit)
    {
        ray.mEnergy = glm::vec3(0.f);
        return glm::vec3(0.f);
    }

    // Diffuse Lighting
    glm::vec3 diffuseColour(0);
    for (auto &light : mLights)
    {
        // Construct a rayToLight and fire it towards the light
        Ray rayToLight = light->getRayToLight(hit.hitPosition);
        if (!getHitInWorld(rayToLight).hit)
        {
            // Nothing was hit, so we can apply some shading.
            lightInfo lightInfo = light->getInfo(hit.hitPosition);

            // Diffuse Colour
            float dot = glm::dot(hit.hitNormal, lightInfo.direction);
            diffuseColour += dot > 0 ? dot * lightInfo.colour : glm::vec3 (0);
        }
    }

    // Specular Lighting
    ray.mDirection = glm::reflect(ray.mDirection, hit.hitNormal);
    ray.mPosition = hit.hitPosition;
    ray.mEnergy = ray.mEnergy * 0.6f;

    return hit.colour * 0.1f + hit.colour * diffuseColour;
}

hitInfo RayTracer::getHitInWorld(const Ray &ray)
{
    hitInfo closestHit{false};
    closestHit.colour = glm::vec3 {0.f};
    float closestHitLength(0);
    // Get the colour that the ray interception returns
    for (auto &actor : mPhysicalObjects)
    {
        hitInfo cur = actor->isIntersecting(ray);
        if (cur.hit)
        {
            float hitDistance = glm::length(closestHit.hitPosition - ray.mPosition);
            if (!closestHit.hit)
            {
                closestHit = cur;
                closestHitLength = hitDistance;
            }
            else
            {
                // compare to the previous hit to see if it is closer.
                if (hitDistance < closestHitLength)
                {
                    closestHit = cur;
                    closestHitLength = hitDistance;
                }
            }
        }
    }
    return closestHit;
}
