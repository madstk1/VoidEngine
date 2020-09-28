#pragma once

ShaderCreationInfo *k_ShaderSkybox = new ShaderCreationInfo(
    "Skybox",
    ShaderVersion::V450,
    ShaderProfile::Core, {
        { ShaderStage::Vertex, R"(
            void main() {
                gl_Position = vec4(ub_MVP.Projection * mat4(mat3(ub_MVP.View)) * vec4(i_Position, 1.0)).xyww;
                o_Position  = i_Position;
            }
        )"},
        { ShaderStage::Fragment, R"(
            void main() {
                o_Color = vec4(texture(ub_Skybox, i_Position).rgb, 1.0);
            }
        )"},
    }
);
