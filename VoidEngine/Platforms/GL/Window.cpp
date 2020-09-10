 #include "glad/glad.h"

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Input/InputManager.hpp>

#include <VoidEngine/Platforms/GL/Window.hpp>
#include <VoidEngine/Platforms/GL/Renderer.hpp>

namespace VOID_NS {
#if defined(VOID_ENABLE_DEBUG)
    void WindowGL::GLDebugCallback(u32 source, u32 type, u32 id, u32 severity, i32 length, const char *msg, const void *) {
        switch(severity) {
            case GL_DEBUG_SEVERITY_HIGH:         Logger::LogFatal   ("GL: %s", msg); break;
            case GL_DEBUG_SEVERITY_MEDIUM:       Logger::LogError   ("GL: %s", msg); break;
            case GL_DEBUG_SEVERITY_LOW:          Logger::LogWarning ("GL: %s", msg); break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::LogInfo    ("GL: %s", msg); break;
        }
    }
#endif

    void WindowGL::ErrorCallback(i32 code, const char *msg) {
        Logger::LogError("GLFW: %d, %s", code, msg);
    }

    void WindowGL::ResizeCallback(GLFWwindow *win, i32 w, i32 h) {
        glViewport(0, 0, w, h);

        ((RendererGL *) g_Renderer)->OnResize(w, h);
    }

    void WindowGL::KeyCallback(GLFWwindow *win, i32 key, i32 scancode, i32 action, i32 mods) {
        switch(key) {
            case GLFW_KEY_W:      Input::m_Keys[Keycode::KeyW]     = (action != GLFW_RELEASE); break;
            case GLFW_KEY_S:      Input::m_Keys[Keycode::KeyS]     = (action != GLFW_RELEASE); break;
            case GLFW_KEY_A:      Input::m_Keys[Keycode::KeyA]     = (action != GLFW_RELEASE); break;
            case GLFW_KEY_D:      Input::m_Keys[Keycode::KeyD]     = (action != GLFW_RELEASE); break;
            case GLFW_KEY_SPACE:  Input::m_Keys[Keycode::KeySpace] = (action != GLFW_RELEASE); break;
            case GLFW_KEY_C:      Input::m_Keys[Keycode::KeyC]     = (action != GLFW_RELEASE); break;
        }
    }

    void WindowGL::HandleMouse() {
        static Vector2d lastMouse = {0.0f, 0.0f};
        Vector2d mousePosition = {0.0f, 0.0f};

        glfwGetCursorPos(m_Window, &mousePosition.x, &mousePosition.y);

        Input::m_Cursor.x = mousePosition.x - lastMouse.x;
        Input::m_Cursor.y = lastMouse.y - mousePosition.y;

        lastMouse = mousePosition;
    }

    WindowGL::WindowGL(ApplicationInfo info) : Window(info) {
        glfwSetErrorCallback(ErrorCallback);

        VOID_ASSERT(glfwInit(), "Failed to initialize GLFW.");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  5);
        glfwWindowHint(GLFW_OPENGL_PROFILE,         GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE,              m_Resizable);

#if defined(VOID_ENABLE_DEBUG)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,   GLFW_TRUE);
#endif

        if(info.RefreshRate != -1) {
            glfwWindowHint(GLFW_REFRESH_RATE,       info.RefreshRate);
        }

        this->m_Monitor = glfwGetPrimaryMonitor();
        this->m_Window = glfwCreateWindow(
            m_Size.x, m_Size.y,
            m_Title.c_str(),
            m_Fullscreen ? this->m_Monitor : nullptr,
            nullptr
        );

        if(!this->m_Window) {
            glfwTerminate();
            Logger::LogFatal("Failed to create GLFW window.");
        }

        glfwMakeContextCurrent(this->m_Window);
        glfwSetWindowPos(this->m_Window, m_Position.x, m_Position.y);

        /* NOTE(max): GLFW callbacks */
        glfwSetFramebufferSizeCallback(this->m_Window, ResizeCallback);
        glfwSetKeyCallback(this->m_Window, KeyCallback);
        glfwSetInputMode(this->m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        VOID_ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to bind GLAD to GLFW.");

        /* NOTE(max): Enable DEBUG output. */
#if defined(VOID_ENABLE_DEBUG)
        i32 flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if(!(flags & GL_CONTEXT_FLAG_DEBUG_BIT) || !GLAD_GL_ARB_debug_output) {
            Logger::LogError("Debugging is enabled, but the GL-context does not support it.");
        } else {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    
            glDebugMessageCallback(GLDebugCallback, nullptr);
            glDebugMessageControl(
                GL_DONT_CARE,
                GL_DONT_CARE,
                GL_DEBUG_SEVERITY_NOTIFICATION,
                0, nullptr,
                GL_FALSE
            );
        }
#endif

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CCW);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_FRAMEBUFFER_SRGB);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Logger::LogInfo("Finished intializing GLFW.");
    }

    WindowGL::~WindowGL() {
        glfwDestroyWindow(this->m_Window);
        glfwTerminate();

        Logger::LogInfo("Deallocated GLFW window.");
    }

    void WindowGL::SetTitle(std::string title) {
        glfwSetWindowTitle(this->m_Window, title.c_str());
        m_Title = title;
    }

    void WindowGL::SetPosition(Vector2i pos) {
        glfwSetWindowPos(this->m_Window, pos.x, pos.y);
        m_Position = pos;
    }

    void WindowGL::SetSize(Vector2u size) {
        glfwSetWindowSize(this->m_Window, size.x, size.y);
        m_Size = size;
    }

    void WindowGL::SetBackgroundColor(Color bg) {
        m_Background = bg;
    }

    void WindowGL::SetResizable(bool resizable) {
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        m_Resizable = resizable;
    }

    void WindowGL::SetFullscreen(bool fullscreen) {
        glfwSetWindowMonitor(
            this->m_Window,
            (fullscreen) ? this->m_Monitor : nullptr,
            m_Position.x, m_Position.y,
            m_Size.x, m_Size.y,
            g_Renderer->GetRefreshRate()
        );
        m_Fullscreen = fullscreen;
    }
};
