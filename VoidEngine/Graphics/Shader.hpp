#pragma once

#include <map>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Graphics/RenderTypes.hpp>

namespace VOID_NS {
    struct ShaderCreationInfo {
        string name;

        GLSLVersion version;
        GLSLProfile profile;

        std::map<ShaderStage, string> sources;
    };

    class Shader {
    protected:
        string m_Name;

    public:
        Shader(ShaderCreationInfo info) {
            m_Name = info.name;
        }

        virtual ~Shader() = default;

        virtual void Enable() = 0;
        virtual void Disable() = 0;

        /**
         *  Uniform setters
         */

        virtual void SetUniform1i(string,  i32) = 0;
        virtual void SetUniform1ui(string, u32) = 0;
        virtual void SetUniform1fv(string, f32) = 0;

        virtual void SetUniform2i(string,  Vector2i) = 0;
        virtual void SetUniform2ui(string, Vector2u) = 0;
        virtual void SetUniform2fv(string, Vector2) = 0;

        virtual void SetUniform3i(string,  Vector3i) = 0;
        virtual void SetUniform3ui(string, Vector3u) = 0;
        virtual void SetUniform3fv(string, Vector3) = 0;

        virtual void SetUniform4i(string,  Vector4i) = 0;
        virtual void SetUniform4ui(string, Vector4u) = 0;
        virtual void SetUniform4fv(string, Vector4) = 0;

        virtual void SetUniformMat2f(string, Mat2) = 0;
        virtual void SetUniformMat3f(string, Mat3) = 0;
        virtual void SetUniformMat4f(string, Mat4) = 0;

        inline string GetName() { return m_Name; }

        static const std::string TranslateString(ShaderStage);
        static const std::string TranslateString(GLSLVersion);
        static const std::string TranslateString(GLSLProfile);

        static const string GLSLInclude();
        static const std::map<ShaderStage, string> StageInclude();
    };

    class ShaderLibrary {
    public:
        static Shader *AddShader(ShaderCreationInfo);
        static Shader *GetShader(string);
        static void CreateDefaultShaders();

    protected:
        static std::map<std::string, Shader *> m_Shaders;

    private:
        ShaderLibrary() {}
        ~ShaderLibrary() = default;
    };
};
