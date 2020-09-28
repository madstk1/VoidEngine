#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Misc/Resource.hpp>
#include <VoidEngine/Graphics/Shader.hpp>

namespace VOID_NS {
    class Material : public Resource {
    public:
        Shader *shader = nullptr;

        Color diffuse;
        f32 metallic;
        f32 roughness;
        f32 occlusion;

        Material() {
            diffuse = Color::White();
        }

        static Material GetDefault() {
            static Material mat;
            return mat;
        }
    };
};
