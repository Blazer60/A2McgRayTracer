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

    auto *s = new Sphere({0.f, 0.f, 10.f},
                         {0.f, 0.f, 0.f},
                         {1.f, 1.f, 1.f},
                         {1.f, 0.f, 0.f},
    1);

    mPhysicalObjects.push_back(s);
    mEntities.push_back(s);
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
    //mcg::setBackground(glm::vec3(1,0,0));
    std::vector<Ray> rays = mMainCamera->generateRays();

    // Loop through all of the pixels assigning them their colour.
    for (int i = 0; i < rays.size() - 1; i++)
    {
        hitInfo closestHit{false};
        closestHit.colour = glm::vec3 {0.f};
        float closestHitLength(0);
        // Get the colour that the ray interception returns
        for (auto &actor : mPhysicalObjects)
        {
            hitInfo cur = actor->isIntersecting(rays[i]);
            if (cur.hit)
            {
                if (!closestHit.hit)
                {
                    closestHit = cur;
                    closestHitLength = glm::length(closestHit.hitPosition - mMainCamera->getPosition());
                }
                else
                {
                    // compare to the previous hit to see if it is closer.
                    if (glm::length(cur.hitPosition - mMainCamera->getPosition()) < closestHitLength)
                    {
                        closestHit = cur;
                        closestHitLength = glm::length(closestHit.hitPosition - mMainCamera->getPosition());
                    }
                }
            }
        }
        mPixelBuffer[i] = closestHit.colour;
    }

    for (int i = 0; i < mPixelBuffer.size() - 1; ++i)
    {
        glm::ivec2 pos = {
                i % mWindowSize.x,
                i / mWindowSize.x
        };
        mcg::drawPixel(pos, mPixelBuffer[i]);
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
