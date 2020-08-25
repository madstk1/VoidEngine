#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/ECS/Components/CameraComponent.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/Rendering/Window.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VOID_NS {
    u32 vertexOffset = 0;
    u32 vertexCount = 0;
    u32 indexOffset = 0;
    u32 indexExtension = 0;
    u32 indexCount = 0;

    Renderer::Renderer(ApplicationInfo info) {
        g_Window = Allocator::Allocate<Window>(info);

        SetRefreshRate(info.RefreshRate);
        SetSampling(info.Sampling);
        SetSwapInterval(info.Buffering);

        /* Initialize buffers. */
        glCreateBuffers(1, &m_VertexBuffer);
        glCreateBuffers(1, &m_IndexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * s_MaxTriangles, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * s_MaxTriangles, nullptr, GL_DYNAMIC_DRAW);

        glCreateVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);
    }

    Renderer::~Renderer() {
        Allocator::Free(g_Window);
    }

    void Renderer::Begin() {
        /* Clear screen. */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(
            g_Window->m_Background.r,
            g_Window->m_Background.g,
            g_Window->m_Background.b,
            g_Window->m_Background.a
        );

        /* Calculate camera MVP. */
        glm::mat4 proj = glm::perspective(
            glm::radians(g_Camera->fieldOfView),
            (float) g_Window->m_Size.x / (float) g_Window->m_Size.y,
            g_Camera->zNear,
            g_Camera->zFar
        );

        glm::vec3 camUp = glm::vec3(0, 1, 0);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(
            g_Camera->GameObject()->position,
            g_Camera->GameObject()->position + g_Camera->Forward(),
            camUp
        );

        Shader *shader = ShaderLibrary::GetShader("Default");

        shader->Enable();
        shader->SetUniformMat4f("u_Model",      model);
        shader->SetUniformMat4f("u_View",       view);
        shader->SetUniformMat4f("u_Projection", proj);

        /* Bind entity meshes to buffers. */
        std::vector<u32> tempIndices;
        std::vector<Vertex> tempVertices;
        vertexOffset = 0;
        vertexCount = 0;
        indexOffset = 0;
        indexExtension = 0;
        indexCount = 0;

        MeshComponent *mc; 

        for(Entity *e : g_World->GetEntities()) {
            mc = e->GetComponent<MeshComponent>();
            if(!e->renderable || mc == nullptr) { continue; }
            
            tempIndices = mc->indices;
            tempVertices = mc->vertices;

            for(Vertex &v : tempVertices) {
                v.position *= e->scale;
                v.position += e->position;
            }

            glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
            glBufferSubData(
                GL_ARRAY_BUFFER,
                vertexOffset,
                sizeof(Vertex) * tempVertices.size(),
                tempVertices.data()
            );

            for(u32 &i : tempIndices) {
                i += indexExtension;
            }

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
            glBufferSubData(
                GL_ELEMENT_ARRAY_BUFFER,
                indexOffset,
                sizeof(u32) * tempIndices.size(),
                tempIndices.data()
            );

            vertexOffset += sizeof(Vertex) * tempVertices.size();
            vertexCount += tempVertices.size();

            indexOffset += sizeof(u32) * tempIndices.size();
            indexCount += tempIndices.size();

            indexExtension += tempVertices.size();
        }
    }

    void Renderer::Render() {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::End() {
        glfwPollEvents();
        glfwSwapBuffers(g_Window->m_Window);
    }

    void Renderer::SetRefreshRate(i32 rate) {
        m_RefreshRate = rate;
        glfwWindowHint(GLFW_REFRESH_RATE, (rate == -1) ? GLFW_DONT_CARE : rate);
    }

    void Renderer::SetSampling(MultiSampling samples) {
        m_Sampling = samples;
        glfwWindowHint(GLFW_SAMPLES, samples);

        if(samples == MultiSampling::x0) {
            glDisable(GL_MULTISAMPLE);
        } else {
            glEnable(GL_MULTISAMPLE);
        }
    }

    void Renderer::SetSwapInterval(SwapInterval buffering) {
        m_Buffering = buffering;
        glfwWindowHint(GLFW_DOUBLEBUFFER, m_Buffering == SwapInterval::DoubleBuffer);
        glfwSwapInterval(m_Buffering);

        Logger::LogWarning("Set swap interval: %d", m_Buffering);
    }

    f64 Renderer::GetRenderTime() {
        return glfwGetTime();
    }

    bool Renderer::IsRunning() {
        return !glfwWindowShouldClose(g_Window->m_Window);
    }
};
