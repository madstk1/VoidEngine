#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Misc/Resource.hpp>
#include <VoidEngine/Graphics/Shader.hpp>

namespace VOID_NS {
    /**
     *  Material class.
     *  Holds information about the look of an object
     *  and how to handle it, during rendering.
     */
    class Material : public Resource {
    public:
        /**
         *  The shader object of the material.
         *  By default, this is null, meaning the default shader.
         */
        Shader *shader = nullptr;

        /**
         *  Diffuse- or object-color.
         */
        Color diffuse;

        /**
         *  The metallic surface value.
         *  This changes the way the material reflects and refracts light.
         *
         *  Only values from [0, 1].
         */
        f32 metallic;

        /**
         *  The rougness of the surface.
         *  This changes the way the material scatters light.
         *
         *  Only values from [0, 1].
         */
        f32 roughness;

        /**
         *  The AO (ambient-occlusion) value of the surface.
         *  This affects the shadowing around objects.
         *
         *  Only values from [0, 1].
         */
        f32 occlusion;

        /**
         *  Create default material.
         */
        Material() {
            diffuse = Color::White();
        }

        /**
         *  Return the default material, but using the same UUID.
         *  The prevents creation of new unused materials for meshes.
         */
        static Material GetDefault() {
            static Material mat;
            return mat;
        }
    };
};
