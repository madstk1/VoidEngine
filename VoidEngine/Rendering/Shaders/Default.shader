#ifndef VOID_SHADER_DEFAULT_H__
#define VOID_SHADER_DEFAULT_H__

#include <VoidEngine/Rendering/Shaders/_Shader.hpp>

std::string k_ShaderDefault_vert = R"(#version 450

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec4 i_Color;

layout(location = 0) out vec4 v_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    gl_Position = u_Projection * u_View * u_Model * vec4(i_Position, 1.0);
    v_Color = i_Color;
}
)";

std::string k_ShaderDefault_frag = R"(#version 450

layout(location = 0) in vec4 v_Color;
layout(location = 0) out vec4 o_Color;

void main() {
    o_Color = v_Color;
}
)";

ShaderCreationInfo k_ShaderDefault = {
    "Default", {
        { ShaderStage::StageVertex,     k_ShaderDefault_vert },
        { ShaderStage::StageFragment,   k_ShaderDefault_frag },
    }
};

#endif /* VOID_SHADER_DEFAULT_H__ */
