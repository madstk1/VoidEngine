#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

/* Default shaders */
#include "Shaders/Default.shader"
#include "Shaders/Framebuffer.shader"
#include "Shaders/Skybox.shader"
/* End of default shaders */

namespace VOID_NS {
    const std::string Shader::TranslateString(ShaderStage e) {
        switch(e) {
            case ShaderStage::StageVertex:    return "Vertex";
            case ShaderStage::StageFragment:  return "Fragment";
            case ShaderStage::StageCompute:   return "Compute";
            default: break;
        }
        VOID_ASSERT(false, "Invalid shader-stage enum.");
    }

    /**
     *  SHADER LIBRARY
     */
    std::vector<Shader *> ShaderLibrary::m_Shaders;

    Shader *ShaderLibrary::AddShader(ShaderCreationInfo info) {
        if(GetShader(info.name) != nullptr) {
            Logger::Error("Shader with name '", info.name, "' already exists in shader library.");
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
