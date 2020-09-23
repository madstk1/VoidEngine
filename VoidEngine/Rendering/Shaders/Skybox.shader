#ifndef VOID_SHADER_SKYBOX_H__
#define VOID_SHADER_SKYBOX_H__

ShaderCreationInfo k_ShaderSkybox = {
    "Skybox",
    GLSLVersion::V450, GLSLProfile::Core, {
        { ShaderStage::Vertex, R"(
            void main() {
                gl_Position = vec4(ub_MVP.Projection * ub_MVP.View * vec4(i_Position, 1.0)).xyww;
            })"
        },
        { ShaderStage::Fragment, R"(
            struct vd_ub_Skybox {
                samplerCube Skybox;
            };

            /* Uniform variables. */
            uniform vd_ub_Skybox ub_Skybox;
            
            void main() {
                o_Color = vec4(texture(ub_Skybox.Skybox, i_Position).rgb, 1.0);
            })"
        },
    }
};

#endif /* VOID_SHADER_FRAMEBUFFER_H__ */
