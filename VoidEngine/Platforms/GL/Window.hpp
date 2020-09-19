#ifndef VOID_PLATFORMS_GL_WINDOW_H__
#define VOID_PLATFORMS_GL_WINDOW_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Math/Color.hpp>

#include <VoidEngine/Rendering/Window.hpp>

#include <GLFW/glfw3.h>

namespace VOID_NS {
    class WindowGL : public Window {
    public:
        WindowGL(ApplicationInfo);
        ~WindowGL();

        virtual void SetTitle(std::string) override;
        virtual void SetPosition(Vector2i) override;
        virtual void SetSize(Vector2u) override;
        virtual void SetBackgroundColor(Color) override;
        virtual void SetResizable(bool) override;
        virtual void SetFullscreen(bool) override;

    protected:
        GLFWwindow *m_Window;
        GLFWmonitor *m_Monitor;

        /* Callbacks */
#if defined(VOID_ENABLE_DEBUG)
        static void DebugProxy(u32 source, u32 type, u32 id, u32 severity, i32 length, const char *msg, const void *);
#endif
        static void ErrorProxy(i32, const char *);
        static void ResizeProxy(GLFWwindow *, i32, i32);
        static void KeyProxy(GLFWwindow *, i32, i32, i32, i32);

        void HandleMouse();

        friend class RendererGL;
    };
};

#endif /* VOID_PLATFORMS_GL_WINDOW_H__ */
