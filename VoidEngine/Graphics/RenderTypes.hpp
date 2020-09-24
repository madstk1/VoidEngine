#pragma once

#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    enum class RenderingAPI {
        OpenGL
    };

    enum class ShaderStage {
        Vertex,
        Fragment,
        Compute,
        Geometry,
        TesselationEvaluation,
        TesselationControl,

        Count
    };

    enum class GLSLVersion : u32 {
        V410 = 410,
        V420 = 420,
        V430 = 430,
        V440 = 440,
        V450 = 450,
        V460 = 460,
    };

    enum class GLSLProfile {
        Core,
        Compatibility
    };

    enum class MultiSampling : u32 {
        X0  = 0,
        X1  = 1,
        X2  = 2,
        X4  = 4,
        X8  = 8,
        X16 = 16
    };

    enum class SwapInterval : u32 {
        None = 0,
        Single,
        Double
    };

    typedef enum  {
        ColorBufferBit   = (u32)(1 << 1),
        DepthBufferBit   = (u32)(1 << 2),
        StencilBufferBit = (u32)(1 << 3),
    } ClearFlag;

    enum class CullFace {
        Back,
        Front,
        Both,

        Disabled
    };

    enum class DepthTest {
        Always,
        Never,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual,

        Disabled
    };

    enum class BufferUsage {
        Static,
        Dynamic
    };
};
