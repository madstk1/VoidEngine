#ifndef VOID_RENDERING_SHADER_H__
#define VOID_RENDERING_SHADER_H__

#include <vector>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Rendering/Window.hpp>
#include <VoidEngine/Rendering/Shaders/_Shader.hpp>

#include <glm/glm.hpp>

namespace VOID_NS {
    class Shader {
    public:
        Shader(ShaderCreationInfo);
        ~Shader();

        void Enable();
        void Disable();

        void SetUniform1f(std::string, f32);
        void SetUniform2f(std::string, Vector2);
        void SetUniform3f(std::string, Vector3);
        void SetUniform4f(std::string, Vector4);
        void SetUniformMat2f(std::string, Mat2);
        void SetUniformMat3f(std::string, Mat3);
        void SetUniformMat4f(std::string, Mat4);

        inline std::string GetName() { return m_Name; }

    protected:
        std::string m_Name;
        u32 m_StageID[ShaderStage::StageCount];
        u32 m_Program;

        i32 m_Status;
        i32 m_LogLength;
        std::vector<char> m_ErrorLog;

        i32 GetUniform(std::string);
        void Compile(ShaderCreationInfo);
        void Link(ShaderCreationInfo);
    };

    class ShaderLibrary {
    public:
        static Shader *AddShader(ShaderCreationInfo);
        static Shader *GetShader(std::string);
        static void CreateDefaultShaders();

    protected:
        static std::vector<Shader *> m_Shaders;

    private:
        ShaderLibrary() {}
        ~ShaderLibrary() = default;
    };
};

#endif /* VOID_RENDERING_OPENGL_SHADER_H__ */
