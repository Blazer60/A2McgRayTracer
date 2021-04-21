/**
 * @file RayTracer.cpp.cc
 * @brief The renderer that displays the world to the screen.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */

#include "RayTracer.h"

RayTracer::RayTracer(const glm::ivec2 &mWindowSize) :
    mWindowSize(mWindowSize),
    mShowAmbient(true), mShowDiffuse(true), mShowSpecular(true), mShowSkybox(true)
{
    if(!mcg::init(mWindowSize)) { throw std::exception(); }
    changeScene(lvl::TheDefaultScene);
}

void RayTracer::run()
{
    static unsigned int current = 0;
    static unsigned int last = 0;

    while (mcg::processFrame() && mIsRunning)
    {
        update();
        render();
        event();  // overrides the event system within mcg::processFrame() depending on timing.

        // Get how long the frame took with some useful information
        current = SDL_GetTicks();
        float delta = (static_cast<float>(current - last)) / 1000.f;
        last = current;
        std::cout   << "\rFrame: " << mFrameCount++
                    << "\tFrame Time: " << delta
                    << "\tBounce Limit: " << mBounceLimit << "/" << mMaxBounceLimit;
        // Try and increase the bounce limit of the rays.
        mBounceLimit = glm::min(mMaxBounceLimit, mBounceLimit + 1);
    }
}

void RayTracer::updateAndHold()
{
    update();
    render();
    mcg::showAndHold();  // Waits until the user exits the program.
}

void RayTracer::event()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        if (sdlEvent.type == SDL_QUIT) { mIsRunning = false; }
        if (sdlEvent.type == SDL_KEYDOWN)
        {
            switch (sdlEvent.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    mIsRunning = false;
                    break;
                case SDLK_0:
                    changeScene(lvl::TheDefaultScene);
                    mFrameCount = 0;
                    mBounceLimit = 1;
                    break;
                case SDLK_1:
                    changeScene(lvl::Triangle);
                    mFrameCount = 0;
                    mBounceLimit = 1;
                    break;
                case SDLK_2:
                    changeScene(lvl::MirrorRoom);
                    mFrameCount = 0;
                    mBounceLimit = 1;
                    break;
                case SDLK_3:
                    changeScene(lvl::BasicBall);
                    mFrameCount = 0;
                    mBounceLimit = 1;
            }
        }
    }
}

void RayTracer::update()
{
    for (auto &entity : mEntities)
    {
        entity->update(0.16f);  // Updates as if it was running at 60fps.
    }
}

void RayTracer::render()
{
    // Loop through each pixel coord pair on the screen.
    for (int y = 0; y < mWindowSize.y; ++y)
    {
        for (int x = 0; x < mWindowSize.x; ++x)
        {
            // Pair the coord together.
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

void RayTracer::changeScene(unsigned int index)
{
    if (index == mCurrentScene) { return; }  // Already on the correct scene
    mCurrentScene = index;
    // Deallocate memory from the old scene.
    if (!mEntities.empty())
    {
        for (auto &entity : mEntities)
        {
            delete entity;
        }
        // Reset vectors back to zero elements. Possibly not needed since we use a copy constructor later on.
        mEntities.clear();
        mActors.clear();
        mLights.clear();
        mMainCamera = nullptr;
    }

    scene level = loadScene(mWindowSize, index);
    if (!level.success) { throw std::exception(); }  // The scene doesn't exits. Should never get here.

    // Give ownership to the Ray Tracer
    mEntities = level.entities;
    mActors = level.actors;
    mLights = level.lights;
    mMainCamera = level.mainCamera;
}

glm::vec3 RayTracer::trace(Ray &originRay)
{
    glm::vec3 colour(0);
    Ray ray = originRay;
    for (int i = 0; i < mBounceLimit; ++i)
    {
        hitInfo hit = getHitInWorld(ray);

        // Shadow tracing changes the energy value for the next ray so we take a copy now.
        glm::vec3 energy = ray.mEnergy;

        // Trace shadow will also reflect the ray.
        colour += energy * traceShadows(ray, hit);

        if (glm::dot(ray.mEnergy, ray.mEnergy) < 0.f)
        {
            break;
        }
    }
    return colour;
}

glm::vec3 RayTracer::traceShadows(Ray &ray, const hitInfo &hit)
{
    if (!hit.hit)
    {
        ray.mEnergy = glm::vec3(0.f);
        return mShowSkybox ? sampleSkybox(ray.mDirection) : glm::vec3(0.f);
    }

    // Lighting Calculation.
    glm::vec3 diffuseColour(0);
    glm::vec3 specularColour(0);
    for (auto &light : mLights)
    {
        // Construct a rayToLight and fire it towards the light
        Ray rayToLight = light->getRayToLight(hit.hitPosition);
        rayToLight.mPosition += hit.hitNormal * 0.001f;  // Offset to avoid artifacts from floating point precision.

        if (traceToLightSource(rayToLight, light))
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

    reflectRay(ray, hit);

    // Times by booleans so that we can isolate channels
    return  glm::vec3(mShowAmbient) * hit.material.ambientIntensity +
            glm::vec3(mShowDiffuse) * diffuseColour +
            glm::vec3(mShowSpecular) * specularColour;
}

bool RayTracer::traceToLightSource(const Ray &ray, const LightSource *lightSource)
{
    if (lightSource->mType != lightSource->Directional)  // The light source is not infinitely far away.
    {
        hitInfo lightHit = getHitInWorld(ray);
        if (lightHit.hit)
        {
            // Is the light source closer than the nearest hit?
            return (glm::length(ray.mPosition - lightSource->getPosition()) <
                    glm::length(ray.mPosition - lightHit.hitPosition));
        }
        return true;  // Nothing was hit. Therefore clear line of sight.
    }
    return !quickGetHitInWorld(ray);  // Directional Lights can use quick hit instead.
}

void RayTracer::reflectRay(Ray &ray, const hitInfo &hit)
{
    ray.mDirection = glm::reflect(ray.mDirection, hit.hitNormal);
    ray.mPosition = hit.hitPosition + hit.hitNormal * 0.001f;  // Offset to avoid artifacts from floating point precision.
    ray.mEnergy = ray.mEnergy * hit.material.reflectivityIntensity;
}

hitInfo RayTracer::getHitInWorld(const Ray &ray)
{
    // Brute force method of obtaining the closest hit object in the world.
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
    // Brute force method to see if a ray is ever obstructed.
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
