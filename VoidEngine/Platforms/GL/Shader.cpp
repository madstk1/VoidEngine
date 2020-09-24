#include "glad/glad.h"
#include <VoidEngine/Platforms/GL/Shader.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace VOID_NS {
    ShaderGL::ShaderGL(ShaderCreationInfo info) : Shader(info) {
        if(info.layout.GetPointerSize() == 0) {
            this->m_Layout = Shader::DefaultShaderLayout();
        }

        Compile(info);
        Link(info);

#if defined(VOID_ENABLE_DEBUG)
        glObjectLabel(GL_PROGRAM, this->m_Program, -1, info.name.c_str());

        for(std::pair<ShaderStage, std::string> src : info.sources) {
            std::string name = info.name + " (" + TranslateString(src.first) + ")";
            glObjectLabel(GL_SHADER, m_StageID[(u32) src.first], -1, name.c_str());
        }
#endif
    }
    
    ShaderGL::~ShaderGL() {
        glDeleteProgram(m_Program);
    }

    void ShaderGL::Enable() {
        glUseProgram(m_Program);

        /**
         * Enable vertex attributes.
         *
         * These can be defined in the Shader-file.
         * If not defined, they are defaulted to Shader::DefaultShaderLayout
         */
        u32 i = 0;
        for(const ShaderLayout::LayoutElement &le : m_Layout.GetElements()) {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                i,
                (u32) le.dimension,
                Translate(le.type),
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
        for(u64 i = 0; i < m_Layout.GetElements().Length(); i++) {
            glDisableVertexAttribArray(i);
        }
    }

    /**
     * Uniform setters.
     */

    /* 1D setters */
    void ShaderGL::SetUniform1i(std::string identifier, i32 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform1i(m_Program, loc, val);
        }
    }

    void ShaderGL::SetUniform1ui(std::string identifier, u32 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform1ui(m_Program, loc, val);
        }
    }

    void ShaderGL::SetUniform1fv(std::string identifier, f32 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform1f(m_Program, loc, val);
        }
    }

    /* 2D setters */
    void ShaderGL::SetUniform2i(std::string identifier, Vector2i val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform2i(m_Program, loc, val[0], val[1]);
        }
    }

    void ShaderGL::SetUniform2ui(std::string identifier, Vector2u val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform2ui(m_Program, loc, val[0], val[1]);
        }
    }

    void ShaderGL::SetUniform2fv(std::string identifier, Vector2 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform2fv(m_Program, loc, 1, &val[0]);
        }
    }

    /* 3D setters */
    void ShaderGL::SetUniform3i(std::string identifier, Vector3i val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform3i(m_Program, loc, val[0], val[1], val[2]);
        }
    }

    void ShaderGL::SetUniform3ui(std::string identifier, Vector3u val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform3ui(m_Program, loc, val[0], val[1], val[2]);
        }
    }

    void ShaderGL::SetUniform3fv(std::string identifier, Vector3 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform3fv(m_Program, loc, 1, &val[0]);
        }
    }

    /* 4D setters */
    void ShaderGL::SetUniform4i(std::string identifier, Vector4i val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform4i(m_Program, loc, val[0], val[1], val[2], val[3]);
        }
    }

    void ShaderGL::SetUniform4ui(std::string identifier, Vector4u val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform4ui(m_Program, loc, val[0], val[1], val[2], val[3]);
        }
    }
    void ShaderGL::SetUniform4fv(std::string identifier, Vector4 val) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniform4fv(m_Program, loc, 1, &val[0]);
        }
    }

    /* Matrix setters */
    void ShaderGL::SetUniformMat2f(std::string identifier, Mat2 mat) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniformMatrix2fv(m_Program, loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }

    void ShaderGL::SetUniformMat3f(std::string identifier, Mat3 mat) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniformMatrix3fv(m_Program, loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }

    void ShaderGL::SetUniformMat4f(std::string identifier, Mat4 mat) {
        i32 loc = 0;
        if((loc = GetUniform(identifier)) != -1) {
            glProgramUniformMatrix4fv(m_Program, loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }

    u32 ShaderGL::Translate(ShaderStage e) {
        switch(e) {
            case ShaderStage::Vertex:   return GL_VERTEX_SHADER;
            case ShaderStage::Fragment: return GL_FRAGMENT_SHADER;
            case ShaderStage::Compute:  return GL_COMPUTE_SHADER;

            default: VOID_ASSERT(false, "Invalid shader-stage.");
        }
    }

    u32 ShaderGL::Translate(ShaderLayout::Type e) {
        switch(e) {
            case ShaderLayout::Type::Byte:      return GL_BYTE;
            case ShaderLayout::Type::UByte:     return GL_UNSIGNED_BYTE;
            case ShaderLayout::Type::Short:     return GL_SHORT;
            case ShaderLayout::Type::UShort:    return GL_UNSIGNED_SHORT;
            case ShaderLayout::Type::Int:       return GL_INT;
            case ShaderLayout::Type::UInt:      return GL_UNSIGNED_INT;
            case ShaderLayout::Type::HFloat:    return GL_HALF_FLOAT;
            case ShaderLayout::Type::Float:     return GL_FLOAT;
            case ShaderLayout::Type::Double:    return GL_DOUBLE;

            default: VOID_ASSERT(false, "Invalid layout-type.");
        }
    }

    /**
     *  Private/protected methods
     */

    i32 ShaderGL::GetUniform(std::string identifier) {
        return glGetUniformLocation(m_Program, identifier.c_str());
    }

    void ShaderGL::Compile(ShaderCreationInfo info) {
        char *src_c;
        std::string formattedSource;
        i32 m_Status, m_LogLength;
        std::vector<char> m_ErrorLog;

        for(std::pair<ShaderStage, std::string> src : info.sources) {
            u32 id = m_StageID[(u32) src.first] = glCreateShader(Translate(src.first));

            /* Append GLSL version and profile. */
            formattedSource = "#version " +
                TranslateString(info.version) + " " +
                TranslateString(info.profile) + "\n" + 

            /* Append default inclusions. */
                Shader::DefaultGLSLInclude();

            /* Append stage inclusions. */
            for(auto it : Shader::DefaultStageInclude()) {
                if(it.first == src.first) {
                    formattedSource += it.second;
                }
            }

            /* Append rest of stage source. */
            formattedSource += "\n" + src.second;
            src_c = (char *) formattedSource.c_str();

            glShaderSource(id, 1, &src_c, NULL);
            glCompileShader(id);

            glGetShaderiv(id, GL_COMPILE_STATUS, &m_Status);
            if(m_Status == GL_FALSE) {
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &m_LogLength);
                m_ErrorLog.reserve(m_LogLength);
                glGetShaderInfoLog(id, m_LogLength, &m_LogLength, &m_ErrorLog[0]);
                
                glDeleteShader(id);
                Logger::Error("Failed to compile shader (", info.name, ", ", TranslateString(src.first),  ") ", m_ErrorLog.data());
            }
        }
    }

    void ShaderGL::Link(ShaderCreationInfo info) {
        i32 m_Status, m_LogLength;
        std::vector<char> m_ErrorLog;
        m_Program = glCreateProgram();

        for(std::pair<ShaderStage, std::string> src : info.sources) {
            glAttachShader(m_Program, m_StageID[(u32) src.first]);
        }

        glLinkProgram(m_Program);
        glGetProgramiv(m_Program, GL_LINK_STATUS, &m_Status);
        if(m_Status == GL_FALSE) {
            glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &m_LogLength);
            m_ErrorLog.reserve(m_LogLength);
            glGetProgramInfoLog(m_Program, m_LogLength, &m_LogLength, &m_ErrorLog[0]);

            glDeleteProgram(m_Program);
            for(std::pair<ShaderStage, std::string> src : info.sources) {
                glDeleteShader(m_StageID[(u32) src.first]);
            }
            Logger::Fatal("Failed to link shader: ", m_ErrorLog.data());
        }

        // Detach linked shaders to free memory.
        for(std::pair<ShaderStage, std::string> src : info.sources) {
            glDetachShader(m_Program, m_StageID[(u32) src.first]);
        }
        Logger::Info("Finished compiling shader: ", info.name.c_str());
    }
};
