#ifndef VOID_MISC_TEXTURE_H__
#define VOID_MISC_TEXTURE_H__

#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Resource.hpp>

namespace VOID_NS {
    class Texture : public Resource {
        friend Allocator;

    public:
        virtual ~Texture() = default;

        const inline Vector2i GetSize() const {
            return m_Size;
        }

        const inline uchar *GetData() const {
            return m_Data;
        }

        const inline u32 GetChannelCount() const {
            return m_ChannelCount;
        }

        static Texture *LoadTexture(std::string name, std::string path);
        static void FreeTexture(Texture *);

    protected:
        Vector2i m_Size;
        i32 m_ChannelCount;
        uchar *m_Data;

        Texture(std::string name) : Resource(name, Type::TextureResource) {}

    private:
    };
};

#endif /* VOID_MISC_TEXTURE_H__ */
