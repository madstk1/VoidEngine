#ifndef VOID_SHADER_FRAMEBUFFER_H__
#define VOID_SHADER_FRAMEBUFFER_H__

ShaderCreationInfo k_ShaderFramebuffer = {
    "Framebuffer",
    GLSLVersion::V450, GLSLProfile::Core, {
        { ShaderStage::Vertex, R"(
            void main() {
                gl_Position = vec4(i_Position, 1.0);
                o_TexCoords = i_TexCoords;
            })"
        },
        { ShaderStage::Fragment, R"(
            struct vd_ub_Framebuffer {
                sampler2D ScreenTexture;
            };
            
            /* Uniform variables. */
            uniform vd_ub_Framebuffer ub_Framebuffer;

            void main() {
                o_Color = vec4(texture(ub_Framebuffer.ScreenTexture, i_TexCoords).rgb, 1.0);
            })"
        },
    }
};

#endif /* VOID_SHADER_FRAMEBUFFER_H__ */
