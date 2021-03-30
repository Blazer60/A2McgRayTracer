/**
 * @file LightingMaterials.h
 * @brief The materials that hold information about how light should
 * be reflected, refracted or absorbed by an object.
 * Project: A2McgRayTracer
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 30/03/2021
 */


#ifndef A2MCGRAYTRACER_LIGHTINGMATERIALS_H
#define A2MCGRAYTRACER_LIGHTINGMATERIALS_H

#include "glm.hpp"

/**
 * A material that defines how light behaves when interacting with this surface.
 * This is also used source lights to illuminate the world.
 */
struct lightingMaterial
{
    /**
     * The colour used for unlit scenes. It can also be used to define the ambient,
     * diffuse and specular intensities.
     */
    glm::vec3 baseColour;

    /** The amount of light that reaches anywhere on the surface regardless of lighting. */
    glm::vec3 ambientIntensity;

    /** The colour of the object when in the light. The fall off is equivalent to Lambert's Cosine law */
    glm::vec3 diffuseIntensity;

    /** How shiny an object looks. 0 - matte-like, 1 - shiny */
    glm::vec3 specularIntensity;

    lightingMaterial(const glm::vec3 &baseColour, const glm::vec3 &ambientIntensity, const glm::vec3 &diffuseIntensity,
                     const glm::vec3 &specularIntensity) :
                     baseColour(baseColour),
                     ambientIntensity(ambientIntensity),
                     diffuseIntensity(diffuseIntensity),
                     specularIntensity(specularIntensity)
    {}

    lightingMaterial(const glm::vec3 &baseColour, const glm::vec3 &specularIntensity) :
        baseColour(baseColour),
        ambientIntensity(baseColour * 0.05f),
        diffuseIntensity(baseColour),
        specularIntensity(specularIntensity)
    {}

    explicit lightingMaterial(const glm::vec3 &baseColour) :
        baseColour(baseColour),
        ambientIntensity(baseColour * 0.05f),
        diffuseIntensity(baseColour),
        specularIntensity(1.f)
    {}

    lightingMaterial() :
        baseColour(1.f, 0.f, 0.498f),
        ambientIntensity(baseColour * 0.05f),
        diffuseIntensity(baseColour),
        specularIntensity(0.647f)
    {}
};

/**
 * A material that defines how light behaves when interacting with this surface.
 * It also defines how reflective and transparent an object is.
 */
struct actorLightingMaterial : public lightingMaterial
{
    /** How transparent an object is. 0 - opaque, 1 - transparent. */
    glm::vec3 transmissionIntensity;

    /** How reflective an object is. 0 - matte, 1 - mirror-like. */
    glm::vec3 reflectivityIntensity;

    /**
     * How large the object's specular 'dot' is. 32 - large area, 1024 - small area.
     * @paragraph This value should be proportional to the specular intensity
     * for the most realistic effect. Example pairings: n=2 Ks=0.04, n=10 Ks=0.08,
     * n=50 Ks=0.1, n=250 Ks=0.15, n=1250 Ks=0.2 (Credit to Scratch Pixel the values).
     * @see <a href="https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF">
     *  Scratch Pixel, Phong Model introduction.
     *  </a>
     */
    float shininessConstant;

    actorLightingMaterial(const glm::vec3 &baseColour, const glm::vec3 &ambientIntensity,
                          const glm::vec3 &diffuseIntensity, const glm::vec3 &specularIntensity,
                          const glm::vec3 &transmissionIntensity, const glm::vec3 &reflectivityIntensity,
                          float shininessConstant) :
                          lightingMaterial(baseColour, ambientIntensity, diffuseIntensity, specularIntensity),
                          transmissionIntensity(transmissionIntensity),
                          reflectivityIntensity(reflectivityIntensity),
                          shininessConstant(shininessConstant)
    {}

    actorLightingMaterial(const glm::vec3 &baseColour, const glm::vec3 &specularIntensity,
                          const glm::vec3 &reflectivityIntensity, float shininessConstant) :
                          lightingMaterial(baseColour, specularIntensity),
                          reflectivityIntensity(reflectivityIntensity),
                          shininessConstant(shininessConstant)
    {}

    actorLightingMaterial() :
        transmissionIntensity(0.f),
        reflectivityIntensity(0.38f),
        shininessConstant(2048.f)
    {}
};

#endif //A2MCGRAYTRACER_LIGHTINGMATERIALS_H
