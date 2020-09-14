#include "glad/glad.h"
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
    Vertex k_QuadVertices[] = {
        Vertex(Vector3(-1.0f, -1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3( 1.0f, -1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3( 1.0f,  1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-1.0f,  1.0f, -1.0f), Color::White(), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 1.0f)),
    };

    u32 k_QuadIndices[] = {
        0, 1, 2,
        2, 3, 0
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

    RendererGL::BufferDataGL::BufferDataGL(BufferUsage usage) : BufferData(usage) {
        glCreateBuffers(1, &VBO);
        glCreateBuffers(1, &EBO);
        glCreateVertexArrays(1, &VAO);
    }

    RendererGL::BufferDataGL::~BufferDataGL() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void RendererGL::BufferDataGL::Bind() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    RendererGL::RendererGL(ApplicationInfo info) : Renderer(info) {
        g_Window = Allocator::Allocate<WindowGL>(info);

        SetRefreshRate(info.RefreshRate);
        SetSampling(info.Sampling);
        SetSwapInterval(info.Buffering);

        /**
         *  Initialize vertex-buffers.
         */

        m_Static  = new BufferDataGL(BufferUsage::StaticBufferUsage);
        m_Dynamic = new BufferDataGL(BufferUsage::DynamicBufferUsage);

        m_Dynamic->Bind();

        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * s_MaxTriangles, nullptr, GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * s_MaxTriangles, nullptr, GL_DYNAMIC_DRAW);

        /**
         *  Initialize renderquad buffers.
         */

        m_RenderQuad = new BufferDataGL(BufferUsage::StaticBufferUsage);
        m_RenderQuad->Bind();

        glBufferData(GL_ARRAY_BUFFER,         sizeof(k_QuadVertices), k_QuadVertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(k_QuadIndices),  k_QuadIndices,  GL_STATIC_DRAW);

        /**
         *  Initialize skybox-buffers.
         */

        m_Skybox = new BufferDataGL(BufferUsage::StaticBufferUsage);
        m_Skybox->Bind();

        glBufferData(GL_ARRAY_BUFFER, sizeof(k_SkyboxVertices), k_SkyboxVertices, GL_STATIC_DRAW);
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

        /**
         *  Generate multi-sampled texture.
         */

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_TextureColorbuffer);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, GetWindow()->GetSize().x, GetWindow()->GetSize().y, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_TextureColorbuffer, 0);

        /**
         *  Generate renderbuffer.
         */

        glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);

        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, GetWindow()->GetSize().x, GetWindow()->GetSize().y);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Renderbuffer);

        VOID_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        /**
         *  Create intermediate framebuffer.
         */

        glBindFramebuffer(GL_FRAMEBUFFER, m_IntermediateFBO);

        glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetWindow()->GetSize().x, GetWindow()->GetSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ScreenTexture, 0);

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
        Logger::LogDebug("Deallocating OpenGL-renderer.");

        glDeleteFramebuffers(1, &m_Framebuffer);
        glDeleteFramebuffers(1, &m_IntermediateFBO);
        glDeleteRenderbuffers(1, &m_Renderbuffer);

        glDeleteTextures(1, &m_TextureColorbuffer);
        glDeleteTextures(1, &m_ScreenTexture);
            
        Allocator::Free(m_Dynamic);
        Allocator::Free(m_Static);
        Allocator::Free(GetWindow());
    }

    Shader *RendererGL::CreateShader(ShaderCreationInfo info) {
        return Allocator::Allocate<ShaderGL>(info);
    }

    void RendererGL::Begin() {
        this->Prepare();
        GetWindow()->HandleMouse();

        /* Bind framebuffer. */
        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
        glEnable(GL_DEPTH_TEST);
        ClearColor();

        /* Bind entity meshes to buffers. */
        this->UpdateBuffers(m_Dynamic);

        static bool ff = true;
        if(ff) {
            ff = false;
            this->UpdateBuffers(m_Static);
        }
    }

    void RendererGL::Render() {
        Shader *defaultShader      = ShaderLibrary::GetShader("Default");
        Shader *skyboxShader       = ShaderLibrary::GetShader("Skybox");
        Shader *framebufferShader  = ShaderLibrary::GetShader("Framebuffer");

        /* Calculate camera MVP. */
        f32 aspectRatio = (f32) g_Window->GetSize().x / (f32) g_Window->GetSize().y;

        Mat4 model = glm::mat4(1.0f);
        Mat4 proj  = glm::perspective(glm::radians(g_Camera->fieldOfView), aspectRatio, g_Camera->zNear, g_Camera->zFar);
        Mat4 view  = glm::lookAt(g_Camera->position, g_Camera->position + g_Camera->Forward(), {0, 1, 0});

        /**
         *  Render dynamic entites.
         */

        m_Dynamic->Bind();
        SetLightMatrix(defaultShader);

        defaultShader->SetUniform1fv("u_Gamma",          m_Gamma);
        defaultShader->SetUniform3fv("u_CameraPosition", g_Camera->position);
        defaultShader->SetUniformMat4f("u_Model",        model);
        defaultShader->SetUniformMat4f("u_View",         view);
        defaultShader->SetUniformMat4f("u_Projection",   proj);

        glDrawElements(GL_TRIANGLES, m_Dynamic->indices.size(), GL_UNSIGNED_INT, (const void *) 0);
        
        /**
         *  Render static entites.
         */

        m_Static->Bind();
        SetLightMatrix(defaultShader);

        defaultShader->SetUniform1fv("u_Gamma",          m_Gamma);
        defaultShader->SetUniform3fv("u_CameraPosition", g_Camera->position);
        defaultShader->SetUniformMat4f("u_Model",        model);
        defaultShader->SetUniformMat4f("u_View",         view);
        defaultShader->SetUniformMat4f("u_Projection",   proj);

        glDrawElements(GL_TRIANGLES, m_Static->indices.size(), GL_UNSIGNED_INT, (const void *) 0);

        /**
         *  Draw skybox.
         */

        if(glIsTexture(m_SkyboxCubemap)) {
            glDepthFunc(GL_LEQUAL);
            glDisable(GL_CULL_FACE);
    
            m_Skybox->Bind();
            skyboxShader->Enable();
            skyboxShader->SetUniformMat4f("u_Projection", proj);
            skyboxShader->SetUniformMat4f("u_View", Mat4(Mat3(view)));
    
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyboxCubemap);
            glDrawElements(GL_TRIANGLES, LEN(k_SkyboxIndices), GL_UNSIGNED_INT, (const void *) 0);
    
            glEnable(GL_CULL_FACE);
            glDepthFunc(GL_LESS);
        }

        /**
         *  Blit multisampled buffer to normal buffer.
         */

        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_IntermediateFBO);
        glBlitFramebuffer(
            0, 0, GetWindow()->GetSize().x, GetWindow()->GetSize().y,
            0, 0, GetWindow()->GetSize().x, GetWindow()->GetSize().y,
            GL_COLOR_BUFFER_BIT, GL_NEAREST
        );

        /**
         *  Unbind framebuffer and render to texture.
         */

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        ClearColor();

        /**
         *  Draw rendering quad.
         */

        m_RenderQuad->Bind();
        framebufferShader->Enable();
        framebufferShader->SetUniform1i("u_ScreenTexture", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);

        glDrawElements(GL_TRIANGLES, LEN(k_QuadIndices), GL_UNSIGNED_INT, (const void *) 0);
    }

    void RendererGL::End() {
        glfwPollEvents();
        glfwSwapBuffers(GetWindow()->m_Window);
    }

    void RendererGL::SetSkybox(Cubemap *skybox) {
        if(glIsTexture(m_SkyboxCubemap)) {
            glDeleteTextures(1, &m_SkyboxCubemap);
        }

        std::array<Texture *, 6> textures = skybox->GetTextures();
        Texture *sample = textures[0];

        u32 width  = sample->GetSize().x;
        u32 height = sample->GetSize().y;
        u32 format = (sample->GetChannelCount() == 4) ? GL_RGBA : GL_RGB;

        glGenTextures(1, &m_SkyboxCubemap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyboxCubemap);

        /* Specify face data. */
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textures[0]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textures[1]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textures[2]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textures[3]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textures[4]->GetData());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textures[5]->GetData());

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
        /* NOTE: OpenGL does not like a sample-count of 0, in glTexImage2DMultisample. */
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

    void RendererGL::UpdateBuffers(BufferDataGL *buffer) {
        u32 usage[] = {
            [BufferUsage::DynamicBufferUsage] = GL_DYNAMIC_DRAW,
            [BufferUsage::StaticBufferUsage]  = GL_STATIC_DRAW,
        };

        Renderer::UpdateBuffersImpl(buffer);

        buffer->Bind();
        glBufferData(GL_ARRAY_BUFFER,         sizeof(Vertex) * buffer->vertices.size(), buffer->vertices.data(), usage[buffer->usage]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32)    * buffer->indices.size(),  buffer->indices.data(),  usage[buffer->usage]);
    }

    void RendererGL::PrintExtensions() {
        i32 nExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

        for(i32 i = 0; i < nExtensions; i++) {
            const uchar *ext = glGetStringi(GL_EXTENSIONS, i);
            Logger::LogInfo("[EXT] %s", ext);
        }
    }

    void RendererGL::SetLightMatrix(Shader *shader) {
        shader->Enable();

        u32 i = 0;
        for(Light *light : g_World->GetLights()) {
            if(i >= 32) { break; }
            shader->SetUniform3fv("u_LightingData[" + std::to_string(i) + "].color",     light->lightColor);
            shader->SetUniform3fv("u_LightingData[" + std::to_string(i) + "].position",  light->position);
            shader->SetUniform1fv("u_LightingData[" + std::to_string(i) + "].intensity", light->intensity);
            i++;
        }
    
        shader->SetUniform1ui("u_LightCount",     i);
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
