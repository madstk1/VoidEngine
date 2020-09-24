#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Graphics/Renderer.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Misc/Singleton.hpp>

namespace VOID_NS {
    class RendererGL : public Renderer, Singleton<RendererGL> {
    protected:
        GLFWwindow  *m_Window;
        GLFWmonitor *m_Monitor;

        /* Buffers */

        /* Framebuffers / renderbuffers. */

        /* Textures / cubemaps */

        /* Shaders */

    public:
        RendererGL();
        ~RendererGL();

        virtual void Begin() override;
        virtual void Draw() override;
        virtual void End() override;

        virtual f64 RenderTime() override;
        virtual bool IsRunning() override;
        virtual Vector<string> GetExtensions() override;

        virtual void Clear(ClearFlag) override;
        
        /**
         *  Setters
         */

        virtual void SetTitle(std::string) override;
        virtual void SetSize(Vector2u) override;
        virtual void SetPosition(Vector2i) override;
        virtual void SetMaxFPS(i32) override;
        virtual void SetBackground(Color) override;
        virtual void SetFullscreen(bool) override;
        virtual void SetResizable(bool) override;
        virtual void SetSampling(MultiSampling) override;
        virtual void SetBuffering(SwapInterval) override;
        virtual void SetCulling(CullFace) override;
        virtual void SetDepthTestFunc(DepthTest) override;
    };
};
