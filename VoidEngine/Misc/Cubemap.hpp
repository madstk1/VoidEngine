#ifndef VOID_MISC_CUBEMAP_H__
#define VOID_MISC_CUBEMAP_H__

#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Texture.hpp>

namespace VOID_NS {
    class Cubemap : public Resource {
    public:
        typedef enum {
            Right,  Left,
            Top,    Bottom,
            Front,  Back
        } CubemapFaces;

        Cubemap(std::string name, std::array<Texture *, 6> textures) : Resource(name, Resource::Type::CubemapResource) {
            m_Textures = textures;
        }

        const inline std::array<Texture *, 6> GetTextures() const { return m_Textures; }

    protected:
        std::array<Texture *, 6> m_Textures;
        
    private:
    };
};

#endif /* VOID_MISC_CUBEMAP_H__ */
