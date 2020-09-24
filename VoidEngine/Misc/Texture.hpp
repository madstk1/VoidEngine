#ifndef VOID_MISC_TEXTURE_H__
#define VOID_MISC_TEXTURE_H__

#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class Texture {
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

        static Texture *LoadTexture(std::string path);
        static void FreeTexture(Texture *);

    protected:
        Vector2i m_Size;
        i32 m_ChannelCount;
        uchar *m_Data;

        Texture() {}

    private:
    };
};

#endif /* VOID_MISC_TEXTURE_H__ */
