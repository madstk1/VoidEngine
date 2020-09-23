#ifndef VOID_PLATFORMS_GL_RENDERER_H__
#define VOID_PLATFORMS_GL_RENDERER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Material.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>
#include <VoidEngine/Platforms/GL/Buffers.hpp>

namespace VOID_NS {
    class WindowGL;

    class RendererGL : public Renderer {
    protected:
        struct RenderObjectGL {
            Entity *entity = nullptr;
            GeometryBufferGL *buffer = nullptr;
            Material *material = nullptr;

            bool indexed = true;
        };

        Vector<RenderObjectGL> m_RenderObjects;

        /* Buffers */
        GeometryBufferGL   *m_Skybox;
        GeometryBufferGL   *m_RenderQuad;

        /* Framebuffers / renderbuffers */
        u32                 m_Framebuffer;
        u32                 m_IntermediateFBO;
        u32                 m_Renderbuffer;

        /* Textures */
        u32                 m_TextureColorbuffer;
        u32                 m_ScreenTexture;
        u32                 m_SkyboxCubemap;

        Shader             *m_DefaultShader;
        Shader             *m_FramebufferShader;
        Shader             *m_SkyboxShader;
        MVP                 m_MVP;

        void SetLightMatrix(Shader *);
        void ClearColor();

        void CreateRenderObject(Entity *);
        void UpdateRenderObjects();
        bool CheckRenderObjects(Entity *);

        WindowGL *GetWindow();

    public:
        RendererGL(ApplicationInfo);
        ~RendererGL();

        virtual Shader *CreateShader(ShaderCreationInfo) override;

        virtual void Begin() override;
        virtual void End() override;
        virtual void Render() override;

        virtual f64 GetRenderTime() override;
        virtual bool IsRunning() override;

        virtual void SetSkybox(Cubemap *) override;
        virtual void SetRefreshRate(i32) override;
        virtual void SetSampling(MultiSampling) override;
        virtual void SetSwapInterval(SwapInterval) override;

        std::vector<std::string> GetExtensions() override;

        friend WindowGL;
    };
};

#endif /* VOID_PLATFORMS_GL_RENDERER_H__ */
