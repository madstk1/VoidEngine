#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Rendering/Shader.hpp>
#include <VoidEngine/Rendering/GLAD/GLAD.h>

#include <glm/gtc/type_ptr.hpp>

/* Default shaders */
#include "Shaders/Default.shader"
#include "Shaders/Framebuffer.shader"
#include "Shaders/Skybox.shader"
/* End of default shaders */

namespace VOID_NS {
    /**
     *  SHADER LIBRARY
     */
    std::vector<Shader *> ShaderLibrary::m_Shaders;

    Shader *ShaderLibrary::AddShader(ShaderCreationInfo info) {
        if(GetShader(info.name) != nullptr) {
            Logger::LogError("Shader with name '%s' already exists in shader library.", info.name.c_str());
            return nullptr;
        }

        Shader *shader = g_Renderer->CreateShader(info);
        m_Shaders.push_back(shader);

        return shader;
    }

    Shader *ShaderLibrary::GetShader(std::string name) {
        for(Shader *shader : m_Shaders) {
            if(shader->GetName() == name) {
                return shader;
            }
        }
        return nullptr;
    }

    void ShaderLibrary::CreateDefaultShaders() {
        AddShader(k_ShaderDefault);
        AddShader(k_ShaderFramebuffer);
        AddShader(k_ShaderSkybox);
    }
};
