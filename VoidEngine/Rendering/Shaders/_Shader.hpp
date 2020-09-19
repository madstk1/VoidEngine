#ifndef VOID_RENDERING_SHADERS_SHADER_H__
#define VOID_RENDERING_SHADERS_SHADER_H__

#include <string>
#include <vector>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    class ShaderLayout {
    public:
        enum Type {
            Byte, UByte,
            Short, UShort,
            Int, UInt,
            HFloat, Float,
            Double
        };

        enum Dimension {
            L1D = 1,
            L2D = 2,
            L3D = 3,
            L4D = 4
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
        Vertex = 0,
        Fragment,
        Compute,
        TessControl,
        TessEvaluation,
        Geometry,

        StageCount
    };

    struct ShaderCreationInfo {
        std::string name;
        std::string version;
        std::vector<std::pair<ShaderStage, std::string>> sources;
        ShaderLayout layout;
    };
};

using namespace VOID_NS;

#endif /* VOID_RENDERING_SHADERS_SHADER_H__ */
