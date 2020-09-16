#include "glad/glad.h"
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Platforms/GL/Renderer.hpp>

namespace VOID_NS {
    /**
     *  Geometry buffer
     */

    RendererGL::GeometryBufferGL::GeometryBufferGL(BufferUsage usage) : GeometryBuffer(usage) {
        glCreateBuffers(1, &VBO);
        glCreateBuffers(1, &EBO);
        glCreateVertexArrays(1, &VAO);
    }

    RendererGL::GeometryBufferGL::~GeometryBufferGL() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void RendererGL::GeometryBufferGL::Bind() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    /**
     *  Shader buffer
     */
 
    RendererGL::ShaderBufferGL::ShaderBufferGL(BufferUsage usage) : ShaderBuffer(usage) {
        glCreateBuffers(1, &VBO);
        glCreateBuffers(1, &EBO);
        glCreateVertexArrays(1, &VAO);
    }

    RendererGL::ShaderBufferGL::~ShaderBufferGL() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void RendererGL::ShaderBufferGL::Bind() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }
};

