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
        tex->m_Data = stbi_load(path.c_str(), &tex->m_Size.x, &tex->m_Size.y, &tex->m_ChannelCount, 0);

        if(!tex->m_Data) {
            Logger::Error("Failed to load texture: ", path);

            stbi_image_free(tex->m_Data);
            return nullptr;
        }

        return tex;
    }

    void Texture::FreeTexture(Texture *tex) {
        stbi_image_free(tex->m_Data);
        Allocator::Free(tex);
    }
};

