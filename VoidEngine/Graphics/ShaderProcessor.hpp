#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Graphics/Shader.hpp>
#include <VoidEngine/Memory/Allocator.hpp>

namespace VOID_NS {
    class ShaderProcessor {
    public:
        static void Initialize();
        static void Destroy();

        static void ProcessShader(ShaderCreationInfo *, RenderingAPI);

        static string TranslateString(ShaderStage);

    protected:
    };
};
