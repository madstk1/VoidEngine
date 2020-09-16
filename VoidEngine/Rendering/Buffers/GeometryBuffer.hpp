#ifndef VOID_RENDERING_BUFFERS_GEOMETRY_BUFFER_H__
#define VOID_RENDERING_BUFFERS_GEOMETRY_BUFFER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Rendering/Buffers/Buffer.hpp>

namespace VOID_NS {
    class GeometryBuffer : public Buffer {
    public:
        Vector<Vertex> vertices;
        Vector<u32>    indices;

        GeometryBuffer() {}
        GeometryBuffer(BufferUsage usage) : Buffer(usage) {}

        GeometryBuffer(
            Vector<Vertex> vertices,
            Vector<u32> indices
        ) : vertices(vertices), indices(indices) {}

        GeometryBuffer(
            BufferUsage usage,
            Vector<Vertex> vertices,
            Vector<u32> indices
        ) : Buffer(usage), vertices(vertices), indices(indices) {}

        ~GeometryBuffer() = default;

    protected:
    private:
    };
};

#endif /* VOID_RENDERING_BUFFERS_GEOMETRY_BUFFER_H__ */
