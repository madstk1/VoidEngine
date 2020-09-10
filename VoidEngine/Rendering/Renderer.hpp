#ifndef VOID_RENDERING_RENDERER_H__
#define VOID_RENDERING_RENDERER_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>

#include <VoidEngine/Rendering/Window.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

namespace VOID_NS {
    class Renderer {
    protected:
        static const u32 s_MaxTriangles = 100000;

        i32             m_RefreshRate;
        MultiSampling   m_Sampling;
        SwapInterval    m_Buffering;

    public:
        Renderer(ApplicationInfo) {}
        virtual ~Renderer() = default;

        virtual Shader *CreateShader(ShaderCreationInfo) = 0;

        virtual void Begin() = 0;
        virtual void End() = 0;
        virtual void Render() = 0;

        virtual f64 GetRenderTime() = 0;
        virtual bool IsRunning() = 0;

        virtual void SetRefreshRate(i32) = 0;
        virtual void SetSampling(MultiSampling) = 0;
        virtual void SetSwapInterval(SwapInterval) = 0;

        virtual i32 GetRefreshRate() { return m_RefreshRate; }
        virtual MultiSampling GetSampling() { return m_Sampling; }
        virtual SwapInterval GetSwapInterval() { return m_Buffering; }
    };
};

#endif /* VOID_RENDERING_RENDERER_H__ */
