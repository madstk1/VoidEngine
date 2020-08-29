#include <VoidEngine/Rendering/Shader.hpp>
#include <VoidEngine/Rendering/GLAD/GLAD.h>

#include <glm/gtc/type_ptr.hpp>

/* Default shaders */
#include "Shaders/Default.shader"
/* End of default shaders */

namespace VOID_NS {
    const static u32 k_Stages[] = {
        [ShaderStage::StageVertex]   = GL_VERTEX_SHADER,
        [ShaderStage::StageFragment] = GL_FRAGMENT_SHADER,
        [ShaderStage::StageCompute]  = GL_COMPUTE_SHADER,
    };

    Shader::Shader(ShaderCreationInfo info) {
        m_Name = info.name;
        Compile(info);
        Link(info);
    }
    
    Shader::~Shader() {
        glDeleteProgram(m_Program);
    }

    void Shader::Enable() {
        glUseProgram(m_Program);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
    }

    void Shader::Disable() {
        glUseProgram(0);
    }

    void Shader::SetUniformMat2f(std::string identifier, Mat2 mat) {
    
    }

    void Shader::SetUniformMat3f(std::string identifier, Mat3 mat) {
    
    }

    void Shader::SetUniformMat4f(std::string identifier, Mat4 mat) {
        i32 loc = glGetUniformLocation(m_Program, identifier.c_str());
        if(loc != -1) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
        } else {
            Logger::LogError("Invalid uniform identifier '%s'", identifier.c_str());
        }
    }

    void Shader::Compile(ShaderCreationInfo info) {
        for(std::pair<ShaderStage, std::string> src : info.sources) {
            m_StageID[src.first] = glCreateShader(k_Stages[src.first]);
            u32 id = m_StageID[src.first];

            const char *src_ = src.second.c_str();
            glShaderSource(id, 1, &src_, NULL);
            glCompileShader(id);

            glGetShaderiv(id, GL_COMPILE_STATUS, &m_Status);
            if(m_Status == GL_FALSE) {
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &m_LogLength);
                m_ErrorLog.reserve(m_LogLength);
                glGetShaderInfoLog(id, m_LogLength, &m_LogLength, &m_ErrorLog[0]);
                
                glDeleteShader(id);
                Logger::LogFatal("Failed to compile shader: %s", m_ErrorLog.data());
            }
        }
    }

    void Shader::Link(ShaderCreationInfo info) {
        m_Program = glCreateProgram();
        for(std::pair<ShaderStage, std::string> src : info.sources) {
            glAttachShader(m_Program, m_StageID[src.first]);
        }

        glLinkProgram(m_Program);
        glGetProgramiv(m_Program, GL_LINK_STATUS, &m_Status);
        if(m_Status == GL_FALSE) {
            glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &m_LogLength);
            m_ErrorLog.reserve(m_LogLength);
            glGetProgramInfoLog(m_Program, m_LogLength, &m_LogLength, &m_ErrorLog[0]);

            glDeleteProgram(m_Program);
            for(std::pair<ShaderStage, std::string> src : info.sources) {
                glDeleteShader(m_StageID[src.first]);
            }
            Logger::LogFatal("Failed to link shader: %s", m_ErrorLog.data());
        }

        // Detach linked shaders to free memory.
        for(std::pair<ShaderStage, std::string> src : info.sources) {
            glDetachShader(m_Program, m_StageID[src.first]);
        }
        Logger::LogInfo("Finished compiling shader: %s", info.name.c_str());
    }

    /**
     *  SHADER LIBRARY
     */
    std::vector<Shader *> ShaderLibrary::m_Shaders;

    Shader *ShaderLibrary::AddShader(ShaderCreationInfo info) {
        if(GetShader(info.name) != nullptr) {
            Logger::LogError("Shader with name '%s' already exists in shader library.", info.name.c_str());
            return nullptr;
        }

        Shader *shader = new Shader(info);
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
    }
};
