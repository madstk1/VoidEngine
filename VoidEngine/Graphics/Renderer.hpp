#pragma once

#include <VoidEngine/Memory/Allocator.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Graphics/Shader.hpp>

namespace VOID_NS {
    class Renderer {
    public:
        Renderer() {}
        virtual ~Renderer() = default;

        virtual void Initialize() = 0;
        virtual void Destroy() = 0;

        virtual void Begin() = 0;
        virtual void Draw() = 0;
        virtual void End() = 0;

        virtual void SetCullFace(CullFace) = 0;
        virtual void SetFrontFace(FrontFace) = 0;
        virtual void SetDepthTest(DepthTest) = 0;

        virtual void Clear(ClearFlag) = 0;
        virtual void SwapBuffers() = 0;

        Ptr<Shader> CreateShader(ShaderCreationInfo);
    };
};
