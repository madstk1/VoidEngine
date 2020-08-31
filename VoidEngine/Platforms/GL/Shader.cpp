#include "../../Rendering/GLAD/GLAD.h"
#include <VoidEngine/Platforms/GL/Shader.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace VOID_NS {
    const static u32 k_Stages[] = {
        [ShaderStage::StageVertex]   = GL_VERTEX_SHADER,
        [ShaderStage::StageFragment] = GL_FRAGMENT_SHADER,
        [ShaderStage::StageCompute]  = GL_COMPUTE_SHADER,
    };

    const static u32 k_AttributeType[] = {
        [ShaderLayout::Type::Byte]      = GL_BYTE,
        [ShaderLayout::Type::UByte]     = GL_UNSIGNED_BYTE,
        [ShaderLayout::Type::Short]     = GL_SHORT,
        [ShaderLayout::Type::UShort]    = GL_UNSIGNED_SHORT,
        [ShaderLayout::Type::Int]       = GL_INT,
        [ShaderLayout::Type::UInt]      = GL_UNSIGNED_INT,
        [ShaderLayout::Type::HFloat]    = GL_HALF_FLOAT,
        [ShaderLayout::Type::Float]     = GL_FLOAT,
        [ShaderLayout::Type::Double]    = GL_DOUBLE,
    };

    ShaderGL::ShaderGL(ShaderCreationInfo info) : Shader(info) {
        Compile(info);
        Link(info);
    }
    
    ShaderGL::~ShaderGL() {
        glDeleteProgram(m_Program);
    }

    void ShaderGL::Enable() {
        glUseProgram(m_Program);

        /**
         * Enable vertex attributes.
         * These should be defined in the Shader-file.
         */
        u32 i = 0;
        for(const ShaderLayout::LayoutElement &le : m_Layout.GetElements()) {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                i,
                le.dimension,
                k_AttributeType[le.type],
                (le.normalized) ? GL_TRUE : GL_FALSE,
                m_Layout.GetPointerSize(),
                (const void *) le.offset
            );
            i++;
        }
    }

    void ShaderGL::Disable() {
        glUseProgram(0);

        /**
         * Disable vertex attributes.
         * Read ShaderGL::Enable().
         */
        for(u64 i = 0; i < m_Layout.GetElements().size(); i++) {
            glDisableVertexAttribArray(i);
        }
    }

    /**
     * Uniform setters.
     */
    void ShaderGL::SetUniform1i(std::string identifier, i32 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniform1i(loc, val);
        }
    }

    void ShaderGL::SetUniform1ui(std::string identifier, u32 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniform1ui(loc, val);
        }
    }

    void ShaderGL::SetUniform1fv(std::string identifier, f32 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniform1f(loc, val);
        }
    }

    void ShaderGL::SetUniform2fv(std::string identifier, Vector2 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniform2fv(loc, 1, &val[0]);
        }
    }

    void ShaderGL::SetUniform3fv(std::string identifier, Vector3 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniform3fv(loc, 1, &val[0]);
        }
    }

    void ShaderGL::SetUniform4fv(std::string identifier, Vector4 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniform4fv(loc, 1, &val[0]);
        }
    }

    void ShaderGL::SetUniformMat2f(std::string identifier, Mat2 mat) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }

    void ShaderGL::SetUniformMat3f(std::string identifier, Mat3 mat) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }

    void ShaderGL::SetUniformMat4f(std::string identifier, Mat4 mat) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }

    /**
     *  Private/protected methods
     */

    i32 ShaderGL::GetUniform(std::string identifier) {
        i32 loc = glGetUniformLocation(m_Program, identifier.c_str());
        if(loc != -1) {
            return loc;
        }

        Logger::LogError("Invalid uniform identifier '%s', %d", identifier.c_str(), loc);
        return -1;
    }


    void ShaderGL::Compile(ShaderCreationInfo info) {
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

    void ShaderGL::Link(ShaderCreationInfo info) {
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
};
