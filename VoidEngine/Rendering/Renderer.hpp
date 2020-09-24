#ifndef VOID_RENDERING_RENDERER_H__
#define VOID_RENDERING_RENDERER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Cubemap.hpp>
#include <VoidEngine/Rendering/Shader.hpp>
#include <VoidEngine/Rendering/Window.hpp>

#include <VoidEngine/Rendering/Buffers/GeometryBuffer.hpp>
#include <VoidEngine/Rendering/Buffers/ShaderBuffer.hpp>
#include <VoidEngine/Rendering/Buffers/UniformBuffer.hpp>

namespace VOID_NS {
    class Renderer {
    protected:
        static const u32 s_MaxTriangles = 800000;

        i32             m_RefreshRate   = 144;
        MultiSampling   m_Sampling      = MultiSampling::x4;
        SwapInterval    m_Buffering     = SwapInterval::SingleBuffer;
        f32             m_Gamma         = 1.8f;

        static void PopulateGeometryBuffer(GeometryBuffer *);
        static void PopulateShaderBuffer(ShaderBuffer *);

        static void CalculateMVP(MVP *);

    public:
        Renderer(ApplicationInfo) {}
        virtual ~Renderer() = default;

        virtual Shader *CreateShader(ShaderCreationInfo) = 0;

        virtual void Begin() = 0;
        virtual void End() = 0;
        virtual void Render() = 0;

        virtual f64 GetRenderTime() = 0;
        virtual bool IsRunning() = 0;

        virtual void SetSkybox(Cubemap *) = 0;
        virtual void SetRefreshRate(i32) = 0;
        virtual void SetSampling(MultiSampling) = 0;
        virtual void SetSwapInterval(SwapInterval) = 0;
        virtual void SetGamma(f32 gamma) { m_Gamma = gamma; }

        virtual i32 GetRefreshRate() { return m_RefreshRate; }
        virtual MultiSampling GetSampling() { return m_Sampling; }
        virtual SwapInterval GetSwapInterval() { return m_Buffering; }
        virtual f32 GetGamma() { return m_Gamma; }
        virtual Vector<std::string> GetExtensions() { return {}; }
    };
};

#endif /* VOID_RENDERING_RENDERER_H__ */
