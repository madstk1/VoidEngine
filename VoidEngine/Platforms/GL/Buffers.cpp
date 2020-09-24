#include "glad/glad.h"
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Platforms/GL/Buffers.hpp>

namespace VOID_NS {
    inline u32 Translate(Buffer::BufferUsage e) {
        switch(e) {
            case Buffer::BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
            case Buffer::BufferUsage::Static:  return GL_STATIC_DRAW;
            default: break;
        }
        VOID_ASSERT(false, "Invalid BufferUsage enum.");
    }

    /**
     *  Geometry buffer
     */

    GeometryBufferGL::GeometryBufferGL(BufferUsage usage) : GeometryBuffer(usage) {
        glCreateBuffers(1, &VBO);
        glCreateBuffers(1, &EBO);
        glCreateVertexArrays(1, &VAO);
    }

    GeometryBufferGL::~GeometryBufferGL() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void GeometryBufferGL::Bind() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    void GeometryBufferGL::Unbind() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    /**
     *  Shader buffer
     */
 
    ShaderBufferGL::ShaderBufferGL(BufferUsage usage) : ShaderBuffer(usage) {
        glCreateBuffers(1, &VBO);
        glCreateBuffers(1, &EBO);
        glCreateVertexArrays(1, &VAO);
    }

    ShaderBufferGL::~ShaderBufferGL() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void ShaderBufferGL::Bind() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    void ShaderBufferGL::Unbind() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    /**
     *  Uniform buffer
     */

    UniformBufferGL::UniformBufferGL(BufferUsage usage, u64 size) : UniformBuffer(usage, size) {
        glCreateBuffers(1, &UBO);
        m_Size = size;

        Bind();
        glBufferData(GL_UNIFORM_BUFFER, m_Size, nullptr, Translate(usage));
    }

    UniformBufferGL::UniformBufferGL(u64 size)
        : UniformBufferGL(BufferUsage::Dynamic, size) {}

    UniformBufferGL::~UniformBufferGL() {
        glDeleteBuffers(1, &UBO);
    }

    void UniformBufferGL::Bind() {
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    }

    void UniformBufferGL::Unbind() {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBufferGL::Update(u64 size, void *data) {
        VOID_ASSERT(size <= m_Size, "Buffer subdata size exceeds allocated size.");

        Bind();
        glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
    }

    void UniformBufferGL::Update(u64 size, u64 offset, void *data) {
        VOID_ASSERT(size <= m_Size, "Buffer subdata size exceeds allocated size.");
        VOID_ASSERT(size + offset <= m_Size, "Buffer subdata size and offset exceeds allocated size.");

        Bind();
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }
};
