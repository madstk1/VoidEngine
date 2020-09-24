#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Graphics/Shader.hpp>

/* Default shaders */
namespace VOID_NS {
    #include "Shaders/Default.shader"
    #include "Shaders/Framebuffer.shader"
    #include "Shaders/Skybox.shader"
};
/* End of default shaders */

namespace VOID_NS {
    /**
     *  Shader
     */

    const std::string Shader::TranslateString(ShaderStage e) {
        switch(e) {
            case ShaderStage::Vertex:         return "Vertex";
            case ShaderStage::Fragment:       return "Fragment";
            case ShaderStage::Compute:        return "Compute";
            case ShaderStage::Geometry:       return "Geometry";
            case ShaderStage::TesselationControl:    return "Tessellation Control";
            case ShaderStage::TesselationEvaluation: return "Tessellation Evaluation";
            default: break;
        }
        VOID_ASSERT(false, "Invalid shader-stage enum.");
    }

    const std::string Shader::TranslateString(GLSLVersion e) {
        switch(e) {
            case GLSLVersion::V410:  return "410";
            case GLSLVersion::V420:  return "420";
            case GLSLVersion::V430:  return "430";
            case GLSLVersion::V440:  return "440";
            case GLSLVersion::V450:  return "450";
            case GLSLVersion::V460:  return "460";
        }
        VOID_ASSERT(false, "Invalid GLSL-version enum.");
    }

    const std::string Shader::TranslateString(GLSLProfile e) {
        switch(e) {
            case GLSLProfile::Core:          return "core";
            case GLSLProfile::Compatibility: return "compatiblity";
        }
        VOID_ASSERT(false, "Invalid GLSL-profile enum.");
    }

    /**
     *  SHADER LIBRARY
     */

    std::map<std::string, Shader *> ShaderLibrary::m_Shaders;

    Shader *ShaderLibrary::AddShader(ShaderCreationInfo info) {
        if(GetShader(info.name) != nullptr) {
            Logger::Error("Shader with name '", info.name, "' already exists in shader library.");
            return nullptr;
        }

        VOID_ASSERT(false, "fix this, you daft cunt");
        // Shader *shader = g_Renderer->CreateShader(info);
        //m_Shaders.emplace(info.name, shader);
        //return shader;
    }

    Shader *ShaderLibrary::GetShader(std::string name) {
        for(auto s : m_Shaders) {
            if(s.first == name) {
                return s.second;
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
