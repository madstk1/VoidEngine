#ifndef VOID_MISC_MATERIAL_H__
#define VOID_MISC_MATERIAL_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

namespace VOID_NS {
    class Material {
    protected:
        static u32 m_MaterialCount;

    public:
        Color   albedo      = Color::White();
        f32     metallic    = 0.0f;
        f32     roughness   = 1.0f;
        f32     occlusion   = 1.0f;

        std::string name    = "Material";

        Shader *shader;

        Material() : Material("Material " + std::to_string(m_MaterialCount)) {
            m_MaterialCount++;
        }

        Material(std::string name) {
            shader = ShaderLibrary::GetShader("Default");
            this->name = name;
        }

        virtual ~Material() = default;

        static inline Material *GetDefault() {
            static Material mat("Default");
            return &mat;
        }
    };
};

#endif /* VOID_MISC_MATERIAL_H__ */
