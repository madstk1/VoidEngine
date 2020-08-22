#ifndef VOID_RENDERING_SHADER_H__
#define VOID_RENDERING_SHADER_H__

#include <vector>
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

        void SetUniformMat2f(std::string, glm::mat2);
        void SetUniformMat3f(std::string, glm::mat3);
        void SetUniformMat4f(std::string, glm::mat4);

        inline std::string GetName() { return m_Name; }

    protected:
        std::string m_Name;
        u32 m_StageID[ShaderStage::StageCount];
        u32 m_Program;

        i32 m_Status;
        i32 m_LogLength;
        std::vector<char> m_ErrorLog;

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
