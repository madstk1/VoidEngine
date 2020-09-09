#ifndef VOID_PLATFORMS_GL_RENDERER_H__
#define VOID_PLATFORMS_GL_RENDERER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>

namespace VOID_NS {
    class WindowGL;

    class RendererGL : public Renderer {
    protected:
        /* Buffers */
        u32             m_VertexBuffer;
        u32             m_IndexBuffer;
        u32             m_VertexArray;

        /* Framebuffers / renderbuffers */
        u32             m_Framebuffer;
        u32             m_IntermediateFBO;
        u32             m_Renderbuffer;

        /* Textures */
        u32             m_TextureColorbuffer;
        u32             m_ScreenTexture;

        static void PrintExtensions();
        WindowGL *GetWindow();

        void OnResize(i32, i32);
        void ClearColor();

    public:
        RendererGL(ApplicationInfo);
        ~RendererGL();

        virtual Shader *CreateShader(ShaderCreationInfo) override;

        virtual void Begin() override;
        virtual void End() override;
        virtual void Render() override;

        virtual f64 GetRenderTime() override;
        virtual bool IsRunning() override;

        virtual void SetRefreshRate(i32) override;
        virtual void SetSampling(MultiSampling) override;
        virtual void SetSwapInterval(SwapInterval) override;

        friend WindowGL;
    };
};

#endif /* VOID_PLATFORMS_GL_RENDERER_H__ */
