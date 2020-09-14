#ifndef VOID_RENDERING_RENDERER_H__
#define VOID_RENDERING_RENDERER_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Cubemap.hpp>
#include <VoidEngine/Rendering/Window.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

namespace VOID_NS {
    class Renderer {
    protected:
        typedef struct {
            std::vector<Vertex> vertices;
            std::vector<u32>    indices;
        } BufferData;

        static const u32 s_MaxTriangles = 800000;

        i32             m_RefreshRate;
        MultiSampling   m_Sampling;
        SwapInterval    m_Buffering;
        f32             m_Gamma = 1.5f;
        
        void Prepare();
        void UpdateBuffers(BufferData *);
        void UpdateStaticBuffers(BufferData *);

        void UpdateBufferImpl(BufferData *, bool);

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
    };
};

#endif /* VOID_RENDERING_RENDERER_H__ */
