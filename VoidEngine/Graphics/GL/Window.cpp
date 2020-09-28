#include "glad/glad.h"
#include <VoidEngine/Core/Engine.hpp>
#include <VoidEngine/Graphics/GL/Renderer.hpp>
#include <VoidEngine/Graphics/GL/Helper.hpp>

namespace VOID_NS {
    void RendererGL::SetCullFace(CullFace face) {
        if(face != CullFace::Disabled) {
            glEnable(GL_CULL_FACE);
            glCullFace(Translate(face));
        } else {
            glDisable(GL_CULL_FACE);
        }
    }

    void RendererGL::SetFrontFace(FrontFace face) {
        glFrontFace(Translate(face));
    }

    void RendererGL::SetDepthTest(DepthTest dt) {
        if(dt != DepthTest::Disabled) {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(Translate(dt));
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }

    /**
     *  Proxy methods
     */

    void RendererGL::HandleCallbacks(GLFWwindow *window, GLFWmonitor *monitor) {
        /* Debug callback */
#if defined(VOID_ENABLE_DEBUG)
        i32 flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

        if(!(flags & GL_CONTEXT_FLAG_DEBUG_BIT) || !GLAD_GL_ARB_debug_output) {
            Logger::Error("Debugging is enabled, but the GL-context does not support it.");
        } else {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

            glDebugMessageCallback(DebugProxy, nullptr);
            glDebugMessageControl(
                GL_DONT_CARE,
                GL_DONT_CARE,
                GL_DEBUG_SEVERITY_NOTIFICATION,
                0, nullptr,
                GL_FALSE
            );
        }
#endif

        /* GLFW callbacks */
        glfwSetFramebufferSizeCallback(window, ResizeProxy);
        glfwSetKeyCallback(window, KeyProxy);

        /* Title */
        Engine::Get()->Title.OnChange += [=](string r) {
            glfwSetWindowTitle(window, r.c_str());
        };

        /* Position */
        Engine::Get()->Position.OnChange += [=](Vector2i r) {
            if(r.x == -1 && r.y == -1) { return; }
            glfwSetWindowPos(window, r.x, r.y);
        };

        /* Resizable */
        Engine::Get()->Resizable.OnChange += [=](bool r) {
            glfwWindowHint(GLFW_RESIZABLE, r);
        };

        /* Fullscreen */
        Engine::Get()->Fullscreen.OnChange += [=](bool r) {
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            glfwSetWindowMonitor(
                window,
                (r) ? monitor : nullptr,
                0, 0,
                mode->width, mode->height,
                mode->refreshRate
            );
        };

        /* Multisampling */
        Engine::Get()->Sampling.OnChange += [=](MultiSampling r) {
            glfwWindowHint(GLFW_SAMPLES, (u32) r);

            i32 bind = 0;
            glGetIntegerv(GL_RENDERBUFFER_BINDING, &bind);
            if(bind != 0) {
                Engine::Get()->Size.Set(Engine::Get()->Size.Get());
            }
        };

        /* Buffering */
        Engine::Get()->Buffering.OnChange += [=](SwapInterval r) {
            glfwWindowHint(GLFW_DOUBLEBUFFER, r == SwapInterval::Double);
            glfwSwapInterval((i32) r);
        };
    }

    extern "C" {
        void RendererGL::ErrorProxy(i32 code, const char *msg) {
            Logger::Error("GLFW Error: ", code, ", ", msg);
        }
    
        void RendererGL::ResizeProxy(GLFWwindow *, i32 w, i32 h) {
            glViewport(0, 0, w, h);
            Engine::Get()->Size.Set(Vector2u(w, h));
        }
    
        void RendererGL::KeyProxy(GLFWwindow *, i32 key, i32, i32 action, i32 mods) {
            HandleKeyboard(key, action, mods);
        }
    
        void RendererGL::DebugProxy(u32 source, u32 type, u32 id, u32 severity, i32 length, const char *msg, const void *) {
            if(source == GL_DEBUG_SOURCE_SHADER_COMPILER || source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB) {
                Logger::Debug("Debug fallthrough: shader error.");
                return;
            }
    
            switch(severity) {
                case GL_DEBUG_SEVERITY_HIGH:         Logger::Fatal   ("[", id, "] GL: ", msg); break;
                case GL_DEBUG_SEVERITY_MEDIUM:       Logger::Error   ("[", id, "] GL: ", msg); break;
                case GL_DEBUG_SEVERITY_LOW:          Logger::Warning ("[", id, "] GL: ", msg); break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::Info    ("[", id, "] GL: ", msg); break;
            }
        }
    };
};
