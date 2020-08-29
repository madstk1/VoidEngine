#ifndef VOID_RENDERING_WINDOW_H__
#define VOID_RENDERING_WINDOW_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Math/Color.hpp>

// #include <VoidEngine/Rendering/GLAD/GLAD.h>
#include <GLFW/glfw3.h>

namespace VOID_NS {
    class Window {
    protected:
        std::string m_Title;
        Vector2i    m_Position;
        Vector2u    m_Size;
        Color       m_Background;
        bool        m_Resizable;
        bool        m_Fullscreen;

        GLFWwindow *m_Window;
        GLFWmonitor *m_Monitor;

        /* Callbacks */
#if defined(VOID_ENABLE_DEBUG)
        static void GLDebugCallback(u32 source, u32 type, u32 id, u32 severity, i32 length, const char *msg, const void *);
#endif
        static void ErrorCallback(i32, const char *);
        static void ResizeCallback(GLFWwindow *, i32, i32);
        static void MouseCallback(GLFWwindow *, f64, f64);
        static void KeyCallback(GLFWwindow *, i32, i32, i32, i32);

    public:
        Window(ApplicationInfo);
        ~Window();

        void SetTitle(std::string);
        void SetPosition(Vector2i);
        void SetSize(Vector2u);
        void SetBackgroundColor(Color);
        void SetResizable(bool);
        void SetFullscreen(bool);

        std::string GetTitle()     { return m_Title; }
        Vector2i GetPosition()     { return m_Position; }
        Vector2u GetSize()         { return m_Size; }
        Color GetBackgroundColor() { return m_Background; }
        bool GetResizable()        { return m_Resizable; }
        bool GetFullscreen()       { return m_Fullscreen; }

        friend class Renderer;
    };
};

#endif /* VOID_RENDERING_WINDOW_H__ */
