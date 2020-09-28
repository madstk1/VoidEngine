#pragma once

#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    enum class CullFace {
        Front,
        Back,
        Both,

        Disabled
    };

    enum class FrontFace {
        CW,
        CCW
    };

    typedef enum {
        ClearColor   = (1 << 1),
        ClearDepth   = (1 << 2),
        ClearStencil = (1 << 3),
    } ClearFlag;

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

    enum class ShaderStage {
        Vertex,
        Fragment,
        Geometry,
        Compute,
        TesselationControl,
        TesselationEvaluation,

        Count
    };

    enum class ShaderProfile {
        Core,
        Compatibility
    };

    enum class ShaderVersion : u32 {
        V420 = 420,
        V430 = 430,
        V440 = 440,
        V450 = 450,
        V460 = 460
    };

    enum class BufferUsage {
        Dynamic,
        Static
    };
};
