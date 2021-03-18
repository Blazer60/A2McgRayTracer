/**
 * @file RayTracer.cpp.cc
 * @brief [fill in this secton]
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 18/03/2021
 */

#include "RayTracer.h"

RayTracer::RayTracer(const glm::ivec2 &mWindowSize) : mWindowSize(mWindowSize)
{
    if(!mcg::init(mWindowSize)) { throw std::exception(); }
}

void RayTracer::update()
{
    for (auto &entity : mEntities)
    {
        entity->update(1);
    }
}

void RayTracer::render()
{
    mcg::setBackground(glm::vec3(1,0,0));


}

void RayTracer::updateAndHold()
{
    update();
    render();
    mcg::showAndHold();
}
