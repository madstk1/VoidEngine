#pragma once

#include <VoidEngine/Memory/Allocator.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Graphics/Shader.hpp>

namespace VOID_NS {
    class Renderer {
    public:
        void Initialize();
        void Destroy();

        void Render();

        Ptr<Shader> CreateShader(ShaderCreationInfo);

        virtual const f64 GetTime() const = 0;

    protected:
        Renderer() {}
        virtual ~Renderer() = default;

        virtual void InitializeInt() = 0;
        virtual void DestroyInt() = 0;

        virtual void Begin() = 0;
        virtual void Draw() = 0;
        virtual void End() = 0;
        virtual void SwapBuffers() = 0;

        virtual void SetCullFace(CullFace) = 0;
        virtual void SetFrontFace(FrontFace) = 0;
        virtual void SetDepthTest(DepthTest) = 0;
        virtual void Clear(ClearFlag) = 0;

        virtual Vector<string> GetExtensions() = 0;
    };
};
