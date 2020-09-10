#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM

#include "../../ThirdParty/stb/stb_image.h"

namespace VOID_NS {
    Texture *Texture::LoadTexture(std::string name, std::string path) {
        Texture *tex = Allocator::Allocate<Texture>(name);
        uchar *data = stbi_load(path.c_str(), &tex->m_Size.x, &tex->m_Size.y, &tex->m_ChannelCount, 0);

        tex->m_Data = (Color *) Allocator::Allocate(tex->m_Size.x * tex->m_Size.y, sizeof(Color));

        if(!data) {
            Logger::LogError("Failed to load texture: %s", path.c_str());

            stbi_image_free(data);
            return nullptr;
        }

        for(i32 i = 0, j = 0; i < tex->m_Size.x * tex->m_Size.y; i++, j += tex->m_ChannelCount) {
            f32 r = ((f32) data[j + 0]) / 255.0f;
            f32 g = ((f32) data[j + 1]) / 255.0f;
            f32 b = ((f32) data[j + 2]) / 255.0f;

            tex->m_Data[i] = Color(r, g, b, 1.0f);

            if(tex->m_ChannelCount == 4) {
                f32 a = ((f32) data[i + 3]) / 255.0f;
                tex->m_Data[i].a = a;
            }
        }

        stbi_image_free(data);
        return tex;
    }

    void Texture::FreeTexture(Texture *tex) {
        Allocator::Free(tex->m_Data);
        Allocator::Free(tex);
    }
};

