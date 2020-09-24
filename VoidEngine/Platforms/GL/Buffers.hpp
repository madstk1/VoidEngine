#ifndef VOID_PLATFORMS_GL_BUFFERS_H__
#define VOID_PLATFORMS_GL_BUFFERS_H__

#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Rendering/Window.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>

namespace VOID_NS {
    struct GeometryBufferGL : public GeometryBuffer {
        u32 VBO, EBO, VAO;
    
        GeometryBufferGL(BufferUsage);
        ~GeometryBufferGL();
    
        virtual void Bind() override;
        virtual void Unbind() override;
    };
    
    struct ShaderBufferGL : public ShaderBuffer {
        u32 VBO, EBO, VAO;
    
        ShaderBufferGL(BufferUsage);
        ~ShaderBufferGL();
    
        virtual void Bind() override;
        virtual void Unbind() override;
    };

    struct UniformBufferGL : public UniformBuffer {
        u32 UBO;

        UniformBufferGL(u64);
        UniformBufferGL(BufferUsage, u64);

        ~UniformBufferGL();
    
        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void Update(u64, void *) override;
        virtual void Update(u64, u64, void *) override;
    };
};

#endif /* VOID_PLATFORMS_GL_BUFFERS_H__ */
