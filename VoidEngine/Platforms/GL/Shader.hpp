#ifndef VOID_PLATFORMS_GL_SHADER_H__
#define VOID_PLATFORMS_GL_SHADER_H__

#include <vector>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Rendering/Window.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

#include <glm/glm.hpp>

namespace VOID_NS {
    class ShaderGL : public Shader {
    protected:
        u32 m_StageID[(u32) ShaderStage::StageCount];
        u32 m_Program;

        i32 GetUniform(std::string);
        void Compile(ShaderCreationInfo);
        void Link(ShaderCreationInfo);

    public:
        ShaderGL(ShaderCreationInfo);
        ~ShaderGL();

        virtual void Enable() override;
        virtual void Disable() override;

        /* Uniform setters. */
        virtual void SetUniform1i(std::string,  i32) override;
        virtual void SetUniform1ui(std::string, u32) override;
        virtual void SetUniform1fv(std::string, f32) override;

        virtual void SetUniform2i(std::string,  Vector2i) override;
        virtual void SetUniform2ui(std::string, Vector2u) override;
        virtual void SetUniform2fv(std::string, Vector2) override;

        virtual void SetUniform3i(std::string,  Vector3i) override;
        virtual void SetUniform3ui(std::string, Vector3u) override;
        virtual void SetUniform3fv(std::string, Vector3) override;

        virtual void SetUniform4i(std::string,  Vector4i) override;
        virtual void SetUniform4ui(std::string, Vector4u) override;
        virtual void SetUniform4fv(std::string, Vector4) override;

        virtual void SetUniformMat2f(std::string, Mat2) override;
        virtual void SetUniformMat3f(std::string, Mat3) override;
        virtual void SetUniformMat4f(std::string, Mat4) override;

        static u32 Translate(ShaderStage);
        static u32 Translate(ShaderLayout::Type);
    };
};

#endif /* VOID_PLATFORMS_GL_SHADER_H__ */
