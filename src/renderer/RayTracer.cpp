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
    mShowAmbient(true),
    mShowDiffuse(true),
    mShowSpecular(true),
    mShowSkybox(true)
    {
    if(!mcg::init(mWindowSize)) { throw std::exception(); }
    changeScene(Triangle);
}

void RayTracer::changeScene(unsigned int index)
{
    // Deallocate memory from the old scene.
    if (!mEntities.empty())
    {
        for (auto &entity : mEntities)
        {
            delete entity;
        }
        // Possibly not needed?
        mEntities.clear();
        mActors.clear();
        mLights.clear();
        mMainCamera = nullptr;
    }

    scene level = loadScene(mWindowSize, index);
    if (!level.success) { throw std::exception(); }

    // Give ownership to the Ray Tracer
    mEntities = level.entities;
    mActors = level.actors;
    mLights = level.lights;
    mMainCamera = level.mainCamera;
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
    for (int i = 0; i < 3; ++i)
    {
        hitInfo hit = getHitInWorld(ray);
        glm::vec3 energy = ray.mEnergy;  // Shadow tracing changes the energy value for the next ray.
        colour += energy * traceShadows(ray, hit);  // Trace shadow will also reflect the ray
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
        return mShowSkybox ? sampleSkybox(ray.mDirection) : glm::vec3(0.f);
    }

    // Diffuse Lighting
    glm::vec3 diffuseColour(0);
    glm::vec3 specularColour(0);
    for (auto &light : mLights)
    {
        // Construct a rayToLight and fire it towards the light
        Ray rayToLight = light->getRayToLight(hit.hitPosition);
        rayToLight.mPosition += hit.hitNormal * 0.001f;  // Offset to avoid artifacts from floating point precision.
        if (!quickGetHitInWorld(rayToLight))
        {
            // Nothing was hit, so we can apply some shading.
            lightingMaterial lightInfo = light->getInfo(hit.hitPosition);

            // Diffuse Colour
            float dot = glm::dot(hit.hitNormal, rayToLight.mDirection);
            if (dot > 0)
            {
                diffuseColour += dot * lightInfo.diffuseIntensity * hit.material.diffuseIntensity;
            }

            // specular
            glm::vec3 halfDir = glm::normalize(rayToLight.mDirection - ray.mDirection);
            dot = glm::pow(glm::dot(hit.hitNormal, halfDir), hit.material.shininessConstant);
            if (dot > 0)
            {
                specularColour += dot * lightInfo.specularIntensity * hit.material.specularIntensity;
            }
        }
    }

    // Reflection Ray
    ray.mDirection = glm::reflect(ray.mDirection, hit.hitNormal);
    ray.mPosition = hit.hitPosition + hit.hitNormal * 0.001f;  // Offset to avoid artifacts from floating point precision.
    ray.mEnergy = ray.mEnergy * hit.material.reflectivityIntensity;
    // Times by booleans so that we can isolate channels
    return  glm::vec3(mShowAmbient) * hit.material.ambientIntensity +
            glm::vec3(mShowDiffuse) * diffuseColour +
            glm::vec3(mShowSpecular) * specularColour;
}

hitInfo RayTracer::getHitInWorld(const Ray &ray)
{
    hitInfo closestHit{ false };
    closestHit.hitPosition = glm::vec3 { 0.f };
    float closestHitLength(0);
    // Get the diffuse that the ray interception returns
    for (auto &actor : mActors)
    {
        hitInfo cur = actor->isIntersecting(ray);
        if (cur.hit)
        {
            float hitDistance = glm::length(cur.hitPosition - ray.mPosition);
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

bool RayTracer::quickGetHitInWorld(const Ray &ray)
{
    for (auto &actor : mActors)
    {
        if (actor->quickIsIntersecting(ray))
        {
            return true;
        }
    }
    return false;
}

glm::vec3 RayTracer::sampleSkybox(glm::vec3 rayDirection)
{
    float dot = glm::dot(rayDirection, { 0.f, 1.f, 0.f });
    if (dot < 0)  // Below the horizon
    {
        return mGroundColour;
    }
    else if (0 <= dot && dot < mSkyBottomAngle)
    {
        dot = normalise(dot, 0.f, mSkyBottomAngle);
        return glm::mix(mHorizonColour, mSkyBottomColour, dot);
    }
    dot = normalise(dot, mSkyBottomAngle, 1.f);
    return glm::mix(mSkyBottomColour, mSkyTopColour, dot);
}
