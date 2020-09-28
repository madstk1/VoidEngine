#pragma once

ShaderCreationInfo *k_ShaderFramebuffer = new ShaderCreationInfo(
    "Framebuffer",
    ShaderVersion::V450,
    ShaderProfile::Core, {
        { ShaderStage::Vertex, R"(
            void main() {
                gl_Position = vec4(i_Position, 1.0);
                o_TexCoords = i_TexCoords;
            }
        )"},
        { ShaderStage::Fragment, R"(
            void main() {
                o_Color = vec4(texture(ub_Framebuffer, i_TexCoords).rgb, 1.0);
            }
        )"},
    }
);
