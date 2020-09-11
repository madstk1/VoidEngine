#ifndef VOID_MISC_MATERIAL_H__
#define VOID_MISC_MATERIAL_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Resource.hpp>

namespace VOID_NS {
    class Material : public Resource {
    public:
        Color   albedo      = Color::Red();
        f32     metallic    = 0.0f;
        f32     roughness   = 1.0f;
        f32     occlusion   = 1.0f;

        Material(std::string name)
            : Resource(name, Resource::Type::MaterialResource) {}

        virtual ~Material() = default;

        static inline Material GetDefault() { return Material("Default"); }
    };
};

#endif /* VOID_MISC_MATERIAL_H__ */
