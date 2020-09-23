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

    GeometryBufferGL::GeometryBufferGL(u32 vSize, u32 iSize, BufferUsage usage) : GeometryBuffer(vSize, iSize, usage) {
        glCreateBuffers(1, &VBO);
        glCreateBuffers(1, &EBO);
        glCreateVertexArrays(1, &VAO);

        Bind();
        if(vSize != 0) {
            glBufferData(
                GL_ARRAY_BUFFER,
                vSize * sizeof(Vertex),
                nullptr,
                Translate(usage)
            );
        }

        if(iSize != 0) {
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                iSize * sizeof(Index),
                nullptr,
                Translate(usage)
            );
        }
        Unbind();
    }

    GeometryBufferGL::~GeometryBufferGL() {
        Unbind();

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

    void GeometryBufferGL::Update(Vector<Vertex> vertices, u32 offset) {
        Bind();
        glBufferSubData(
            GL_ARRAY_BUFFER,
            offset,
            vertices.Length() * sizeof(Vertex),
            vertices.GetData()
        );
        Unbind();

        this->vertices = vertices;
    }

    void GeometryBufferGL::Update(Vector<Index> indices, u32 offset) {
        Bind();
        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER,
            offset,
            indices.Length() * sizeof(Index),
            indices.GetData()
        );
        Unbind();

        this->indices = indices;
    }
};
