#ifndef VOID_SHADER_SKYBOX_H__
#define VOID_SHADER_SKYBOX_H__

ShaderCreationInfo k_ShaderSkybox = {
    "Skybox",
    GLSLVersion::V450, GLSLProfile::Core, {
        { ShaderStage::Vertex, R"(
            struct vs_Uniform {
                mat4 u_Projection;
                mat4 u_View;
            };

            /* Input variables. */
            layout(location = 0) in vec3 i_Position;
            layout(location = 1) in vec3 i_Normal;
            layout(location = 2) in vec2 i_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec3 v_TexCoords;
            
            /* Uniform variables. */
            uniform vs_Uniform vs_Void;
            
            void main() {
                gl_Position = vec4(vs_Void.u_Projection * vs_Void.u_View * vec4(i_Position, 1.0)).xyww;
                v_TexCoords = i_Position;
            })"
        },
        { ShaderStage::Fragment, R"(
            struct fs_Uniform {
                samplerCube u_Skybox;
            };

            /* Input variables. */
            layout(location = 0) in vec3 v_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec4 o_Color;
            
            /* Uniform variables. */
            uniform fs_Uniform fs_Void;
            
            void main() {
                o_Color = vec4(texture(fs_Void.u_Skybox, v_TexCoords).rgb, 1.0);
            })"
        },
    }, {
        sizeof(Vertex), {
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, position)  },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, normal)    },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L2D, false, offsetof(Vertex, texCoords) },
        }
    }
};

#endif /* VOID_SHADER_FRAMEBUFFER_H__ */
