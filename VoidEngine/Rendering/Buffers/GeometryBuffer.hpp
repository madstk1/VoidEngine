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
        Vector<Index> indices;

        GeometryBuffer(u32, u32, BufferUsage usage) : Buffer(usage) {}

        virtual ~GeometryBuffer() = default;

        virtual void Bind() {}
        virtual void Unbind() {}
        virtual void Update(Vector<Vertex>, u32 = 0) {}
        virtual void Update(Vector<Index>, u32 = 0) {}

        virtual void Update(Vector<Vertex> v, Vector<Index> i) {
            Update(v);
            Update(i);
        }

        virtual void Update(Vector<Vertex> v, Vector<Index> i, u32 vo = 0, u32 io = 0) {
            Update(v, vo);
            Update(i, io);
        }

    protected:
    private:
    };
};

#endif /* VOID_RENDERING_BUFFERS_GEOMETRY_BUFFER_H__ */
