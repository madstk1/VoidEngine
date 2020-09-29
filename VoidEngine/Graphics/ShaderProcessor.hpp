#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Graphics/Shader.hpp>
#include <VoidEngine/Memory/Allocator.hpp>

namespace VOID_NS {
    /**
     *  Shader processor class, used to create and pre-process shader sources.
     */
    class ShaderProcessor {
    public:
        /**
         *  Initialize the GLSL and SPIR-V compiler.
         */
        static void Initialize();

        /**
         *  Free used resources.
         */
        static void Destroy();

        /**
         *  Process shader creation info, with the specified API.
         *  NOTE: Instead of retuning the result, the passed SCI will the altered.
         */
        static void ProcessShader(ShaderCreationInfo *, RenderingAPI);

    protected:
        static string GetDefaultGLSLInclude();
        static string GetDefaultStageInclude(ShaderStage);
    };
};
