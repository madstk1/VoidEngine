#pragma once

#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    enum class Error : u32 {
        NoError = 0,
        InvalidAPI,
        ErrorAllocation,
        NullPointer,
        InvalidEnum,
    };

    enum class MultiSampling : u32 {
        X1  = 1,
        X2  = 2,
        X4  = 4,
        X8  = 8,
        X16 = 16
    };

    enum class SwapInterval : i32 {
        Disabled = 0,
        Single,
        Double,
    };

    enum class RenderingAPI {
        OpenGL,
        Vulkan
    };
};
