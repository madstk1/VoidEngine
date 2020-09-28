#pragma once

#include <GLFW/glfw3.h>
#include <VoidEngine/Graphics/Renderer.hpp>

namespace VOID_NS {
    class RendererGL : public Renderer {
    protected:
        GLFWwindow  *m_Window;
        GLFWmonitor *m_Monitor;

        static void ErrorProxy(i32, const char *);
        static void ResizeProxy(GLFWwindow *, i32, i32);
        static void KeyProxy(GLFWwindow *, i32, i32, i32, i32);
        static void DebugProxy(u32, u32, u32, u32, i32, const char *, const void *);

        static void HandleCallbacks(GLFWwindow *, GLFWmonitor *);
        static void HandleMouse(GLFWwindow *);
        static void HandleKeyboard(i32, i32, i32);

    public:
        RendererGL() {}
        virtual ~RendererGL() = default;

        virtual void Initialize() override;
        virtual void Destroy() override;

        virtual void Begin() override;
        virtual void Draw() override;
        virtual void End() override;

        virtual void Clear(ClearFlag) override;
        virtual void SwapBuffers() override;

        virtual void SetCullFace(CullFace) override;
        virtual void SetFrontFace(FrontFace) override;
        virtual void SetDepthTest(DepthTest) override;
    };
};
