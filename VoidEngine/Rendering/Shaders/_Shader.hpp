#ifndef VOID_RENDERING_SHADERS_SHADER_H__
#define VOID_RENDERING_SHADERS_SHADER_H__

#include <string>
#include <vector>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    typedef enum {
        StageVertex = 0,
        StageFragment,
        StageCompute,

        StageCount
    } ShaderStage;

    struct ShaderCreationInfo {
        std::string name;
        std::vector<std::pair<ShaderStage, std::string>> sources;
    };
};

using namespace VOID_NS;

#endif /* VOID_RENDERING_SHADERS_SHADER_H__ */
