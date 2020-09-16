#ifndef VOID_RENDERING_BUFFERS_BUFFER_H__
#define VOID_RENDERING_BUFFERS_BUFFER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class Buffer {
    public:
        enum class BufferUsage {
            Dynamic,
            Static
        };

        Buffer() {}
        Buffer(BufferUsage usage)
            : m_Usage(usage) {}

        ~Buffer() = default;

        inline BufferUsage GetUsage() { return m_Usage; }

    protected:
        BufferUsage m_Usage;
    };
};

#endif /* VOID_RENDERING_BUFFERS_BUFFER_H__ */
