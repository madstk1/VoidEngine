#include "../..//Rendering/GLAD/GLAD.h"
#include "VoidEngine/Rendering/Shader.hpp"

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/ECS/Entities/Camera.hpp>
#include <VoidEngine/ECS/Entities/Light.hpp>

#include <VoidEngine/Rendering/Renderer.hpp>
#include <VoidEngine/Platforms/GL/Shader.hpp>
#include <VoidEngine/Platforms/GL/Window.hpp>
#include <VoidEngine/Platforms/GL/Renderer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VOID_NS {
    u32 vertexOffset = 0;
    u32 vertexCount = 0;
    u32 indexOffset = 0;
    u32 indexExtension = 0;
    u32 indexCount = 0;

    Mat4 view, proj, model;

    Vertex k_QuadVertices[] = {
        Vertex(Vector3(-1.0f, -1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3( 1.0f, -1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3( 1.0f,  1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-1.0f,  1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 1.0f)),
    };

    u32 k_QuadIndices[] = {
        2, 1, 0,
        0, 3, 2
    };

    Vertex k_SkyboxVertices[] = {
        Vertex(Vector3(-1.0f,  1.0f, -1.0f)),
        Vertex(Vector3(-1.0f, -1.0f, -1.0f)),
        Vertex(Vector3( 1.0f, -1.0f, -1.0f)),
        Vertex(Vector3( 1.0f,  1.0f, -1.0f)),

        Vertex(Vector3(-1.0f, -1.0f,  1.0f)),
        Vertex(Vector3(-1.0f,  1.0f,  1.0f)),
        Vertex(Vector3( 1.0f, -1.0f,  1.0f)),
        Vertex(Vector3( 1.0f,  1.0f,  1.0f)),
    };

    u32 k_SkyboxIndices[] = {
        2, 1, 0, 0, 3, 2,
        4, 1, 0, 0, 5, 4,

        7, 6, 2, 2, 3, 7,
        7, 5, 4, 4, 6, 7,

        7, 3, 0, 0, 5, 7,
        1, 4, 2, 2, 4, 6
    };

    RendererGL::RendererGL(ApplicationInfo info) : Renderer(info) {
        g_Window = Allocator::Allocate<WindowGL>(info);

        SetRefreshRate(info.RefreshRate);
        SetSampling(info.Sampling);
        SetSwapInterval(info.Buffering);

        /**
         *  Initialize vertex-buffers.
         */

        glCreateBuffers(1, &m_VertexBuffer);
        glCreateBuffers(1, &m_IndexBuffer);
        glCreateVertexArrays(1, &m_VertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * s_MaxTriangles, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * s_MaxTriangles, nullptr, GL_DYNAMIC_DRAW);

        /**
         *  Initialize skybox-buffers.
         */

        glCreateBuffers(1, &m_SkyboxVBO);
        glCreateBuffers(1, &m_SkyboxIBO);
        glCreateVertexArrays(1, &m_SkyboxVAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_SkyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(k_SkyboxVertices), k_SkyboxVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SkyboxIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(k_SkyboxIndices), k_SkyboxIndices, GL_STATIC_DRAW);
        
        /**
         *  Initialize framebuffers.
         */

        glCreateFramebuffers(1, &m_Framebuffer);
        glCreateFramebuffers(1, &m_IntermediateFBO);
        glCreateRenderbuffers(1, &m_Renderbuffer);
        glGenTextures(1, &m_TextureColorbuffer);
        glGenTextures(1, &m_ScreenTexture);

        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

        /* Generate multi-sampled texture. */
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_TextureColorbuffer);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, GetWindow()->GetSize().x, GetWindow()->GetSize().y, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_TextureColorbuffer, 0);

        /* Generate renderbuffer. */
        glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, GetWindow()->GetSize().x, GetWindow()->GetSize().y);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        /* Attach renderbuffer to framebuffer. */
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Renderbuffer);

        /* Make sure the framebuffer is valid. Otherwise nothing will render. */
        VOID_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        /* Generate non-multi-sampled texture. */
        glBindFramebuffer(GL_FRAMEBUFFER, m_IntermediateFBO);

        glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetWindow()->GetSize().x, GetWindow()->GetSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ScreenTexture, 0);

        /* Make sure the framebuffer is valid. Otherwise nothing will render. */
        VOID_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Intermediate framebuffer is not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

#if defined(VOID_ENABLE_DEBUG)
        glObjectLabel(GL_FRAMEBUFFER,  m_Framebuffer,     -1, "Framebuffer");
        glObjectLabel(GL_FRAMEBUFFER,  m_IntermediateFBO, -1, "Intermediate FBO");
        glObjectLabel(GL_RENDERBUFFER, m_Renderbuffer,    -1, "Renderbuffer");

        Logger::LogInfo("System information:");
        Logger::LogInfo("   GLFW, v%s", glfwGetVersionString());
        Logger::LogInfo("   Renderer: %s", glGetString(GL_RENDERER));
        Logger::LogInfo("   Version: OpenGL %s", glGetString(GL_VERSION));

        PrintExtensions();
#endif 
    }

    RendererGL::~RendererGL() {
        glDeleteFramebuffers(1, &m_Framebuffer);
        glDeleteFramebuffers(1, &m_IntermediateFBO);
        glDeleteRenderbuffers(1, &m_Renderbuffer);

        glDeleteTextures(1, &m_TextureColorbuffer);
        glDeleteTextures(1, &m_ScreenTexture);
            
        glDeleteVertexArrays(1, &m_VertexArray);
        glDeleteBuffers(1, &m_IndexBuffer);
        glDeleteBuffers(1, &m_VertexBuffer);

        Allocator::Free(g_Window);
    }

    Shader *RendererGL::CreateShader(ShaderCreationInfo info) {
        return Allocator::Allocate<ShaderGL>(info);
    }

    void RendererGL::Begin() {
        GetWindow()->HandleMouse();

        /* Bind framebuffer. */
        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
        glEnable(GL_DEPTH_TEST);
        ClearColor();

        /* Calculate camera MVP. */
        glm::vec3 camUp = glm::vec3(0, 1, 0);

        proj = glm::perspective(
            glm::radians(g_Camera->fieldOfView),
            (float) g_Window->GetSize().x / (float) g_Window->GetSize().y,
            g_Camera->zNear,
            g_Camera->zFar
        );

        model = glm::mat4(1.0f);
        view = glm::lookAt(
            g_Camera->position,
            g_Camera->position + g_Camera->Forward(),
            camUp
        );

        glBindVertexArray(m_VertexArray);

        Shader *shader = ShaderLibrary::GetShader("Default");
        shader->Enable();
        shader->SetUniform1fv("u_Gamma", m_Gamma);

        shader->SetUniformMat4f("u_Model",      model);
        shader->SetUniformMat4f("u_View",       view);
        shader->SetUniformMat4f("u_Projection", proj);
        shader->SetUniform3fv("u_CameraPosition", g_Camera->position);

        u32 i = 0;
        for(Light *light : g_World->GetLights()) {
            if(i >= 32) { break; }

            shader->SetUniform3fv("u_LightingData[" + std::to_string(i) + "].color",     light->lightColor);
            shader->SetUniform3fv("u_LightingData[" + std::to_string(i) + "].position",  light->position);
            shader->SetUniform1fv("u_LightingData[" + std::to_string(i) + "].intensity", light->intensity);
            i++;
        }
        shader->SetUniform1ui("u_LightCount", MIN(g_World->GetLights().size(), 32));

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
            if(!e->renderable || mc == nullptr || mc->mesh == nullptr) { continue; }

            Mat4 transform = Mat4(1.0f)
                * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.x), { 1.0f, 0.0f, 0.0f })
                * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.y), { 0.0f, 1.0f, 0.0f })
                * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.z), { 0.0f, 0.0f, 1.0f })
                * glm::scale(Mat4(1.0f), {e->scale.x, e->scale.y, e->scale.z});
            
            tempIndices = mc->mesh->indices;
            tempVertices = mc->mesh->vertices;

            for(Vertex &v : tempVertices) {
                Vector4 v4 = Vector4(v.position, 1.0f) * transform;
                v.position = Vector3(v4.x, v4.y, v4.z) + e->position;
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

    void RendererGL::Render() {
        glEnable(GL_DEPTH_TEST);

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const void *) 0);

        /* Draw skybox. */
        Shader *sbShader = ShaderLibrary::GetShader("Skybox");
        sbShader->Enable();
        sbShader->SetUniformMat4f("u_Projection", proj);
        sbShader->SetUniformMat4f("u_View", Mat4(Mat3(view)));

        glDepthFunc(GL_LEQUAL);
        glDisable(GL_CULL_FACE);

        glBindVertexArray(m_SkyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_SkyboxVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SkyboxIBO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skybox);
        glDrawElements(GL_TRIANGLES, LEN(k_SkyboxIndices), GL_UNSIGNED_INT, (const void *) 0);

        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);

        /* Blit multisampled buffer to normal buffer. */
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_IntermediateFBO);
        glBlitFramebuffer(
            0, 0,
            GetWindow()->GetSize().x, GetWindow()->GetSize().y,
            0, 0,
            GetWindow()->GetSize().x, GetWindow()->GetSize().y,
            GL_COLOR_BUFFER_BIT,
            GL_NEAREST
        );

        /* Unbind framebuffer and render to texture. */
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        ClearColor();

        /* Draw rendering quad. */
        Shader *fbShader = ShaderLibrary::GetShader("Framebuffer");
        fbShader->Enable();
        fbShader->SetUniform1i("u_ScreenTexture", 0);

        /* TODO: Consider moving to separate buffers. */
        glBindVertexArray(m_VertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(k_QuadVertices), k_QuadVertices);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(k_QuadIndices), k_QuadIndices);

        glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);
        glDrawElements(GL_TRIANGLES, LEN(k_QuadIndices), GL_UNSIGNED_INT, (const void *) 0);
    }

    void RendererGL::End() {
        glfwPollEvents();
        glfwSwapBuffers(GetWindow()->m_Window);
    }

    void RendererGL::SetSkybox(Cubemap *skybox) {
        if(glIsTexture(m_Skybox)) {
            glDeleteTextures(1, &m_Skybox);
        }

        Texture *sample = skybox->GetTextures()[0];

        u32 width = sample->GetSize().x;
        u32 height = sample->GetSize().y;
        u32 format = (sample->GetChannelCount() == 4) ? GL_RGBA : GL_RGB;

        glGenTextures(1, &m_Skybox);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skybox);

        /* Specify face data. */
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, skybox->GetTextures()[0]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, skybox->GetTextures()[1]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, skybox->GetTextures()[2]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, skybox->GetTextures()[3]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, skybox->GetTextures()[4]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, skybox->GetTextures()[5]->GetData());

        /* Filter and wrapping. */
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void RendererGL::SetRefreshRate(i32 rate) {
        m_RefreshRate = rate;
        glfwWindowHint(GLFW_REFRESH_RATE, (rate == -1) ? GLFW_DONT_CARE : rate);
    }

    void RendererGL::SetSampling(MultiSampling samples) {
        /* TODO: OpenGL does not like a sample-count of 0, in glTexImage2DMultisample. */
        m_Sampling = (samples > 1) ? samples : (MultiSampling) 1;

        /* In case no renderbuffer is found, don't update it. */
        i32 rbBinding = 0;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &rbBinding);

        if(rbBinding != 0) {
            OnResize(GetWindow()->GetSize().x, GetWindow()->GetSize().y);
        }
    }

    void RendererGL::SetSwapInterval(SwapInterval buffering) {
        m_Buffering = buffering;
        glfwWindowHint(GLFW_DOUBLEBUFFER, m_Buffering == SwapInterval::DoubleBuffer);
        glfwSwapInterval(m_Buffering);
    }

    f64 RendererGL::GetRenderTime() {
        return glfwGetTime();
    }

    bool RendererGL::IsRunning() {
        return !glfwWindowShouldClose(GetWindow()->m_Window);
    }

    /**
     *  PROTECTED/PRIVATE METHODS
     */

    void RendererGL::PrintExtensions() {
        i32 nExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

        for(i32 i = 0; i < nExtensions; i++) {
            const uchar *ext = glGetStringi(GL_EXTENSIONS, i);
            Logger::LogInfo("[EXT] %s", ext);
        }
    }

    WindowGL *RendererGL::GetWindow() {
        return (WindowGL *) g_Window;
    }

    void RendererGL::OnResize(i32 w, i32 h) {
        GetWindow()->m_Size.x = w;
        GetWindow()->m_Size.y = h;

        /* Resize multi-sampled texture. */
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_TextureColorbuffer);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Sampling, GL_RGB, w, h, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

        /* Resize non-multi-sampled render-texture. */
        glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);

        /* Resize renderbuffer. */
        glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_Sampling, GL_DEPTH24_STENCIL8, w, h);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void RendererGL::ClearColor() {
        uchar depthTest = false;
        glGetBooleanv(GL_DEPTH_TEST, &depthTest);

        glClear(GL_COLOR_BUFFER_BIT | (depthTest ? GL_DEPTH_BUFFER_BIT : 0));
        glClearColor(
            g_Window->GetBackgroundColor().r,
            g_Window->GetBackgroundColor().g,
            g_Window->GetBackgroundColor().b,
            g_Window->GetBackgroundColor().a
        );
    }
};
