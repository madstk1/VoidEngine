#ifndef VOID_RENDERING_RENDERER_H__
#define VOID_RENDERING_RENDERER_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Rendering/Window.hpp>

namespace VOID_NS {
    class Renderer {
    protected:
        static const u32 s_MaxTriangles = 100000;

        i32             m_RefreshRate   = 144;
        MultiSampling   m_Sampling      = MultiSampling::x4;
        SwapInterval    m_Buffering     = SwapInterval::SingleBuffer;

        u32             m_VertexBuffer;
        u32             m_IndexBuffer;
        u32             m_VertexArray;

        static void PrintExtensions();

    public:
        Renderer(ApplicationInfo);
        ~Renderer();

        void Begin();
        void End();
        void Render();

        f64 GetRenderTime();
        bool IsRunning();

        void SetRefreshRate(i32);
        void SetSampling(MultiSampling);
        void SetSwapInterval(SwapInterval);

        i32 GetRefreshRate() { return m_RefreshRate; }
        MultiSampling GetSampling() { return m_Sampling; }
        SwapInterval GetSwapInterval() { return m_Buffering; }
    };
};

#endif /* VOID_RENDERING_RENDERER_H__ */
