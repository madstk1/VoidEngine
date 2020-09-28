#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <VoidEngine/Core/Engine.hpp>
#include <VoidEngine/Graphics/GL/Renderer.hpp>
#include <VoidEngine/Graphics/GL/Helper.hpp>

namespace VOID_NS {
    void RendererGL::Initialize() {
        /**
         *  Initial setup for GLFW.
         */

        glfwSetErrorCallback(ErrorProxy);

        Logger::Assert(glfwInit(), "GLFW failed to initialize.");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, VOID_ENABLE_DEBUG_FLAG);

        /**
         *  Window creation
         */

        this->m_Monitor = glfwGetPrimaryMonitor();
        this->m_Window = glfwCreateWindow(
            Engine::Get()->Size.Get().x,
            Engine::Get()->Size.Get().y,
            Engine::Get()->Title.Get().c_str(),
            Engine::Get()->Fullscreen.Get() ? this->m_Monitor : nullptr,
            nullptr
        );
        Logger::Assert(this->m_Window != nullptr, "Failed to create GLFW window.");

        /**
         *  GLAD binding
         */

        glfwMakeContextCurrent(this->m_Window);
        Logger::Assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to bind GLAD to GLFW.");

        /**
         *  Finaliaztion
         */

        HandleCallbacks(m_Window, m_Monitor);
        Logger::Info("Finished initializing GLFW.");
    }

    void RendererGL::Destroy() {
        glfwDestroyWindow(this->m_Window);
        glfwTerminate();

        Logger::Info("Destroyed GLFW instance.");
    }

    /**
     *  Drawing methods
     */

    void RendererGL::Begin() {
        HandleMouse(this->m_Window);
    }

    void RendererGL::Draw() {
    }

    void RendererGL::End() {
    }

    void RendererGL::SwapBuffers() {
        glfwSwapBuffers(this->m_Window);
        glfwPollEvents();

        /* Handle exit request. */
        if(glfwWindowShouldClose(this->m_Window)) {
            Engine::Get()->Exit();
        }
    }

    void RendererGL::Clear(ClearFlag flag) {
        glClear(Translate(flag));

        if(HASBIT((u32) flag, ClearColor)) {
            Color bg = Engine::Get()->BackgroundColor.Get();
            glClearColor(
                bg.r,
                bg.g,
                bg.b,
                bg.a
            );
        }
    }
};
