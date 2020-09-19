#ifndef VOID_RENDERING_SHADER_H__
#define VOID_RENDERING_SHADER_H__

#include <vector>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Misc/Resource.hpp>
#include <VoidEngine/Rendering/Window.hpp>

#include <glm/glm.hpp>

namespace VOID_NS {
    class ShaderLayout {
    public:
        enum class Type {
            Byte, UByte, Short, UShort, Int, UInt, HFloat, Float, Double
        };

        enum class Dimension {
            L1D = 1,
            L2D, L3D, L4D
        };

        typedef struct {
            Type type;
            Dimension dimension;
            bool normalized;
            u64 offset;
        } LayoutElement;

        ShaderLayout() {}

        ShaderLayout(u64 pointerSize)
            : m_PointerSize(pointerSize) {}

        ShaderLayout(u64 pointerSize, std::initializer_list<LayoutElement> elements)
            : m_PointerSize(pointerSize),
              m_Elements(elements) {}

        void AddElement(LayoutElement element) {
            m_Elements.push_back(element);
        }

        inline u64 GetPointerSize() {
            return m_PointerSize;
        }

        inline std::vector<LayoutElement> GetElements() {
            return m_Elements;
        }

    protected:
        u64 m_PointerSize;
        std::vector<LayoutElement> m_Elements;
    };

    enum class ShaderStage {
        Vertex, Fragment, Compute, TessControl, TessEvaluation, Geometry,
        StageCount
    };

    enum class GLSLVersion {
        V420  = (u32) 420,
        V430  = (u32) 430,
        V440  = (u32) 440,
        V450  = (u32) 450,
        V460  = (u32) 460,
    };

    enum class GLSLProfile {
        Core, Compatibility
    };

    struct ShaderCreationInfo {
        std::string name;
        GLSLVersion version;
        GLSLProfile profile;
        std::vector<std::pair<ShaderStage, std::string>> sources;
        ShaderLayout layout;
    };

    class Shader : Resource {
    protected:
        std::string m_Name;
        ShaderLayout m_Layout;

    public:
        Shader(ShaderCreationInfo info) : Resource(info.name, Type::ShaderResource) {
            m_Name   = info.name;
            m_Layout = info.layout;
        }

        virtual ~Shader() = default;

        virtual void Enable() = 0;
        virtual void Disable() = 0;

        /* Uniform setters. */
        virtual void SetUniform1i(std::string,  i32) = 0;
        virtual void SetUniform1ui(std::string, u32) = 0;
        virtual void SetUniform1fv(std::string, f32) = 0;

        virtual void SetUniform2i(std::string,  Vector2i) = 0;
        virtual void SetUniform2ui(std::string, Vector2u) = 0;
        virtual void SetUniform2fv(std::string, Vector2) = 0;

        virtual void SetUniform3i(std::string,  Vector3i) = 0;
        virtual void SetUniform3ui(std::string, Vector3u) = 0;
        virtual void SetUniform3fv(std::string, Vector3) = 0;

        virtual void SetUniform4i(std::string,  Vector4i) = 0;
        virtual void SetUniform4ui(std::string, Vector4u) = 0;
        virtual void SetUniform4fv(std::string, Vector4) = 0;

        virtual void SetUniformMat2f(std::string, Mat2) = 0;
        virtual void SetUniformMat3f(std::string, Mat3) = 0;
        virtual void SetUniformMat4f(std::string, Mat4) = 0;

        inline std::string GetName() { return m_Name; }

        static const std::string TranslateString(ShaderStage);
        static const std::string TranslateString(GLSLVersion);
        static const std::string TranslateString(GLSLProfile);
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
