#ifndef VOID_PLATFORMS_GL_BUFFERS_H__
#define VOID_PLATFORMS_GL_BUFFERS_H__

#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Rendering/Window.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>
#include <VoidEngine/Rendering/Buffers/GeometryBuffer.hpp>
#include <VoidEngine/Rendering/Buffers/UniformBuffer.hpp>

namespace VOID_NS {
    struct GeometryBufferGL : public GeometryBuffer {
        BufferID VAO = InvalidID;
        BufferID VBO = InvalidID;
        BufferID EBO = InvalidID;
    
        GeometryBufferGL(u32, u32, BufferUsage);
        ~GeometryBufferGL();
    
        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void Update(Vector<Vertex>, u32 = 0) override;
        virtual void Update(Vector<Index>, u32 = 0) override;
    };
    
    struct UniformBufferGL : public UniformBuffer {
        BufferID UBO = InvalidID;

        UniformBufferGL(u64);
        UniformBufferGL(BufferUsage, u64);

        ~UniformBufferGL();
    
        virtual void Bind() override {}
        virtual void Unbind() override {}
        virtual void Update(u64, void *) override {}
        virtual void Update(u64, u64, void *) override {}
    };
};

#endif /* VOID_PLATFORMS_GL_BUFFERS_H__ */
