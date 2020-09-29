#pragma once

#include <VoidEngine/Memory/Allocator.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Graphics/Shader.hpp>

namespace VOID_NS {
    /**
     *  Renderer class interface.
     */
    class Renderer {
    public:
        Renderer() {}
        virtual ~Renderer() = default;

        /**
         *  Initialize the renderer.
         */
        virtual void Initialize() = 0;

        /**
         *  Free resources of the renderer.
         */
        virtual void Destroy() = 0;

        /**
         *  Pre-render render-calls.
         */
        virtual void Begin() = 0;

        /**
         *  Actual render-calls.
         */
        virtual void Draw() = 0;

        /**
         *  Post-render render-calls.
         */
        virtual void End() = 0;

        /**
         *  Set the culling face.
         *  For most model loaders, including Assimp, this should be CullFace::Front.
         */
        virtual void SetCullFace(CullFace) = 0;

        /**
         *  Set the rotation of indices for faces.
         *  Normally, this would be FrontFace::CW.
         */
        virtual void SetFrontFace(FrontFace) = 0;

        /**
         *  Set the depth-testing function.
         *  Normally, this would be DepthTest::Less, since that is default.
         */
        virtual void SetDepthTest(DepthTest) = 0;

        /**
         *  Clear the screen, using the clear-flag.
         */
        virtual void Clear(ClearFlag) = 0;

        /**
         *  Spawn the screen-buffers.
         */
        virtual void SwapBuffers() = 0;

        /**
         *  Create a shader using the renderer, with a ShaderCreationInfo object.
         */
        Ptr<Shader> CreateShader(ShaderCreationInfo);
    };
};
