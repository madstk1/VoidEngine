#ifndef VOID_SHADER_FRAMEBUFFER_H__
#define VOID_SHADER_FRAMEBUFFER_H__

ShaderCreationInfo k_ShaderFramebuffer = {
    "Framebuffer",
    GLSLVersion::V450, GLSLProfile::Core, {
        { ShaderStage::Vertex, R"(
            /* Input variables. */
            layout(location = 0) in vec3 i_Position;
            layout(location = 1) in vec3 i_Normal;
            layout(location = 2) in vec2 i_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec2 v_TexCoords;

            void main() {
                gl_Position = vec4(i_Position, 1.0);
                v_TexCoords = i_TexCoords;
            })"
        },
        { ShaderStage::Fragment, R"(
            struct fs_Uniform {
                sampler2D u_ScreenTexture;
            };
            
            const float PI = 3.1415926535;

            /* Input variables. */
            layout(location = 0) in vec2 v_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec4 o_Color;
            
            /* Uniform variables. */
            uniform fs_Uniform fs_Void;

            void main() {
                o_Color = vec4(texture(fs_Void.u_ScreenTexture, v_TexCoords).rgb, 1.0);
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
