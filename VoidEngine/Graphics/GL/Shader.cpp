#include "glad/glad.h"
#include <VoidEngine/Misc/Translations.hpp>
#include <VoidEngine/Graphics/ShaderProcessor.hpp>
#include <VoidEngine/Graphics/ShaderProcessor.hpp>
#include <VoidEngine/Graphics/GL/Renderer.hpp>

namespace VOID_NS {
    u32 Translate(ShaderStage e) {
        switch(e) {
            case ShaderStage::Vertex:   return GL_VERTEX_SHADER;
            case ShaderStage::Fragment: return GL_FRAGMENT_SHADER;
            case ShaderStage::Compute:  return GL_COMPUTE_SHADER;

            default: break;
        }
        Logger::Assert(false, Translator::TranslateString(Error::InvalidEnum));
        return 0;
    }

    u32 Translate(ShaderType e) {
        switch(e) {
            case ShaderType::Byte:      return GL_BYTE;
            case ShaderType::UByte:     return GL_UNSIGNED_BYTE;
            case ShaderType::Short:     return GL_SHORT;
            case ShaderType::UShort:    return GL_UNSIGNED_SHORT;
            case ShaderType::Int:       return GL_INT;
            case ShaderType::UInt:      return GL_UNSIGNED_INT;
            case ShaderType::HFloat:    return GL_HALF_FLOAT;
            case ShaderType::Float:     return GL_FLOAT;
            case ShaderType::Double:    return GL_DOUBLE;

            default: break;
        }
        Logger::Assert(false, Translator::TranslateString(Error::InvalidEnum));
        return 0;
    }

    ShaderGL::ShaderGL(ShaderCreationInfo info) {
        Vector<u32> stageIDs;
        m_Program = glCreateProgram();

        i32 m_Status, m_LogLength;
        std::vector<char> m_ErrorLog;

        for(auto src : info.sources) {
            u32 id = glCreateShader(Translate(src.first));
            stageIDs.Append(id);

            const char *src_ = src.second.human.c_str();
            glShaderSource(id, 1, &src_, NULL);
            glCompileShader(id);

            glGetShaderiv(id, GL_COMPILE_STATUS, &m_Status);
            if(!m_Status) {
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &m_LogLength);
                m_ErrorLog.reserve(m_LogLength);
                glGetShaderInfoLog(id, m_LogLength, &m_LogLength, &m_ErrorLog[0]);
                
                glDeleteShader(id);
                Logger::Fatal("Failed to compile shader: ", m_ErrorLog.data());
            }
            glAttachShader(m_Program, id);
        }

        glLinkProgram(m_Program);

        glGetProgramiv(m_Program, GL_LINK_STATUS, &m_Status);
        if(!m_Status) {
            glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &m_LogLength);
            m_ErrorLog.reserve(m_LogLength);
            glGetProgramInfoLog(m_Program, m_LogLength, &m_LogLength, &m_ErrorLog[0]);

            glDeleteProgram(m_Program);
            for(u32 i : stageIDs) {
                glDeleteShader(i);
            }
            Logger::Fatal("Failed to link shader: ", m_ErrorLog.data());
        }

        for(u32 i : stageIDs) {
            glDetachShader(m_Program, i);
        }
        Logger::Info("Finished compiling shader: ", info.name);
    }

    void ShaderGL::Enable() {
        glUseProgram(m_Program);
    }

    void ShaderGL::Disable() {
        glUseProgram(0);
    }

    Ptr<Shader> RendererGL::CreateShader(ShaderCreationInfo info) {
        ShaderProcessor::ProcessShader(&info, RenderingAPI::OpenGL);

        ShaderGL *shader = new ShaderGL(info);
        return shader;
    }
};
