#ifndef VOID_RENDERING_BUFFERS_UNIFORM_BUFFER_H__
#define VOID_RENDERING_BUFFERS_UNIFORM_BUFFER_H__

#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Rendering/Buffers/Buffer.hpp>

namespace VOID_NS {
    class UniformBuffer : public Buffer {
    public:
        UniformBuffer(u64 size)
            : m_Size(size) {}

        UniformBuffer(BufferUsage usage, u64 size)
            : Buffer(usage), m_Size(size) {}

        virtual ~UniformBuffer() = default;

        virtual void Bind() {}
        virtual void Unbind() {}
        virtual void Update(u64, void *) {}
        virtual void Update(u64, u64, void *) {}

    protected:
        u64 m_Size;
    };
};

#endif /* VOID_RENDERING_BUFFERS_UNIFORM_BUFFER_H__ */
