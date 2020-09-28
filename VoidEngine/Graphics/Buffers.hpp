#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Misc/Resource.hpp>
#include <VoidEngine/Graphics/RendererTypes.hpp>

namespace VOID_NS {
    struct RenderingBuffer : public Resource {
        Entity *owner;
        const BufferUsage usage;

        RenderingBuffer()
            : usage(BufferUsage::Dynamic) {}

        RenderingBuffer(BufferUsage usage)
            : usage(usage) {}

        virtual ~RenderingBuffer() = default;

        virtual void Bind() {}
        virtual void Unbind() {}
    };

    struct GeometryBuffer : public RenderingBuffer {
        Vector<Vertex> vertices;
        Vector<Index>  indices;

        GeometryBuffer()
            : RenderingBuffer() {}

        GeometryBuffer(BufferUsage usage)
            : RenderingBuffer(usage) {}
    };
};
