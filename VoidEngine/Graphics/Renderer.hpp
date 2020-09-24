#pragma once

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class Renderer {
    protected:
        string      m_Title;

        Vector2u    m_Size;
        Vector2i    m_Position;
        i32         m_MaxFPS;
        f32         m_FixedUpdateInterval;

        Color       m_Background;
        bool        m_Fullscreen;
        bool        m_Resizable;

        MultiSampling m_Sampling;
        SwapInterval m_Buffering;
        CullFace    m_Culling;
        DepthTest   m_DepthTestFunc;

    public:
        Renderer() {
            m_Title         = info.Title;

            m_Size          = info.Size;
            m_Position      = info.Position;
            m_MaxFPS        = info.MaxFPS;
            m_FixedUpdateInterval = info.FixedUpdateInterval;

            m_Background    = info.Background;
            m_Fullscreen    = info.Fullscreen;
            m_Resizable     = info.Resizable;

            m_Sampling      = info.Sampling;
            m_Buffering     = info.Buffering;
            m_Culling       = info.Culling;
            m_DepthTestFunc = info.DepthTestFunc;
        }

        virtual ~Renderer() = default;

        virtual void Begin() {}
        virtual void Draw() {}
        virtual void End() {}

        virtual f64 RenderTime() = 0;
        virtual bool IsRunning() = 0;
        virtual Vector<string> GetExtensions() { return {}; }

        virtual void Clear(ClearFlag) {}

        /**
         *  Getters / setters
         */

        virtual void SetTitle(std::string) = 0;
        virtual void SetSize(Vector2u) = 0;
        virtual void SetPosition(Vector2i) = 0;
        virtual void SetMaxFPS(i32) = 0;
        virtual void SetBackground(Color) = 0;
        virtual void SetFullscreen(bool) = 0;
        virtual void SetResizable(bool) = 0;
        virtual void SetSampling(MultiSampling) = 0;
        virtual void SetBuffering(SwapInterval) = 0;
        virtual void SetCulling(CullFace) = 0;
        virtual void SetDepthTestFunc(DepthTest) = 0;

        virtual std::string GetTitle() { return m_Title; }
        virtual Vector2u GetSize() { return m_Size; }
        virtual Vector2i GetPosition() { return m_Position; }
        virtual i32 GetMaxFPS() { return m_MaxFPS; }
        virtual Color GetBackground() { return m_Background; }
        virtual bool GetFullscreen() { return m_Fullscreen; }
        virtual bool GetResizable() { return m_Resizable; }
        virtual MultiSampling GetSampling() { return m_Sampling; }
        virtual SwapInterval GetBuffering() { return m_Buffering; }
        virtual CullFace GetCulling() { return m_Culling; }
        virtual DepthTest GetDepthTestFunc() { return m_DepthTestFunc; }
    };
};
