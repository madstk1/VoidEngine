#ifndef VOID_SHADER_DEFAULT_H__
#define VOID_SHADER_DEFAULT_H__

#include <VoidEngine/Rendering/Shaders/_Shader.hpp>

ShaderCreationInfo k_ShaderDefault = {
    "Default", "450 core", {
        { ShaderStage::StageVertex, R"(
            struct vs_Uniform {
                mat4 u_Model;
                mat4 u_View;
                mat4 u_Projection;
            };

            /* Input variables. */
            layout(location = 0) in vec3 i_Position;
            layout(location = 1) in vec4 i_Color;
            layout(location = 2) in vec3 i_Normal;
            layout(location = 3) in vec2 i_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec3 v_Position;
            layout(location = 1) out vec4 v_Color;
            layout(location = 2) out vec3 v_Normal;
            layout(location = 3) out vec2 v_TexCoords;
            
            /* Uniform variables. */
            uniform vs_Uniform vs_Void;
            
            void main() {
                mat3 m_Normal = mat3(vs_Void.u_Projection * vs_Void.u_Model);
                m_Normal = inverse(m_Normal);
                m_Normal = transpose(m_Normal);

                gl_Position = vs_Void.u_Projection * vs_Void.u_View * vs_Void.u_Model * vec4(i_Position, 1.0);
                v_Position  = vec3(vs_Void.u_Model * vec4(i_Position, 1.0));
                v_Color     = i_Color;
                v_Normal    = i_Normal * m_Normal;
                v_TexCoords = i_TexCoords;
            }
        )"},
        { ShaderStage::StageFragment, R"(
            struct PointLight {
                vec4 color;
                vec3 position;
                float intensity;
            };

            struct fs_Uniform {
                float      u_Gamma;
                vec3       u_CameraPosition;
                uint       u_LightCount;
                PointLight u_LightingData[32];
            };

            struct fs_Material {
                vec4  u_Albedo;
                float u_Metallic;
                float u_Roughness;
                float u_Occlusion;
            };
            
            /* Input variables. */
            layout(location = 0) in vec3 v_Position;
            layout(location = 1) in vec4 v_Color;
            layout(location = 2) in vec3 v_Normal;
            layout(location = 3) in vec2 v_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec4 o_Color;
            
            /* Uniform variables. */
            uniform fs_Uniform  fs_Void;
            uniform fs_Material fs_Mat;

            vec3 CalculateLight(PointLight light) {
                float distance = distance(light.position, v_Position);
                float attenuation = 1.0 / distance;
            
                vec3 viewDir  = normalize(fs_Void.u_CameraPosition - v_Position);
                vec3 lightDir = normalize(light.position - v_Position);
                vec3 halfDir  = normalize(lightDir + viewDir);
            
                vec3 ambient = light.intensity * light.color.rgb;
                vec3 diffuse = max(dot(v_Normal, lightDir), 0.0) * light.color.rgb / max(0.1, distance);
                vec3 specular = pow(max(0.0, dot(v_Normal, halfDir)), 2.0) * light.color.rgb;
            
                diffuse  *= attenuation;
                specular *= attenuation;
            
                return ambient + diffuse + specular;
            }
            
            void main() {
                vec3 result = vec3(0.0, 0.0, 0.0);

                vec3 N = normalize(v_Normal);
                vec3 V = normalize(fs_Void.u_CameraPosition - v_Position);
            
                for(uint i = 0; i < fs_Void.u_LightCount; i++) {
                    result += CalculateLight(fs_Void.u_LightingData[i]);
                }
            
                // Apply gamma.
                result = pow(result, vec3(1.0 / fs_Void.u_Gamma));
            
                o_Color = vec4(result, 1.0) * fs_Mat.u_Albedo;
            }
        )"},
    }, {
        sizeof(Vertex), {
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, position) },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L4D, false, offsetof(Vertex, color)    },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, normal)   },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L2D, false, offsetof(Vertex, texCoords) },
        }
    }
};

#endif /* VOID_SHADER_DEFAULT_H__ */
