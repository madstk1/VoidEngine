#ifndef VOID_SHADER_DEFAULT_H__
#define VOID_SHADER_DEFAULT_H__

#include <VoidEngine/Rendering/Shaders/_Shader.hpp>

ShaderCreationInfo k_ShaderDefault = {
    "Default", "450 core", {
        { ShaderStage::StageVertex, R"(
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
            uniform mat4 u_Model;
            uniform mat4 u_View;
            uniform mat4 u_Projection;
            
            void main() {
                gl_Position = u_Projection * u_View * u_Model * vec4(i_Position, 1.0);
                v_Position  = vec3(u_Model * vec4(i_Position, 1.0));
                v_Color     = i_Color;
                v_Normal    = i_Normal;
                v_TexCoords = i_TexCoords;
            }
            )"
        },
        { ShaderStage::StageFragment, R"(
            struct PointLight {
                vec4 color;
                vec3 position;
                float intensity;
            };
            
            /* Input variables. */
            layout(location = 0) in vec3 v_Position;
            layout(location = 1) in vec4 v_Color;
            layout(location = 2) in vec3 v_Normal;
            layout(location = 3) in vec2 v_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec4 o_Color;
            
            /* Uniform variables. */
            uniform float u_Gamma;
            uniform vec3 u_CameraPosition;
            uniform uint u_LightCount;
            uniform PointLight u_LightingData[32];
            
            void main() {
                vec3 result = vec3(0.0, 0.0, 0.0);
            
                for(uint i = 0; i < u_LightCount; i++) {
                    float distance = distance(u_LightingData[i].position, v_Position);
                    float attenuation = 1.0 / distance;
            
                    vec3 lightDir = normalize(u_LightingData[i].position - v_Position);
                    vec3 viewDir  = normalize(u_CameraPosition - v_Position);
                    vec3 halfDir  = normalize(lightDir + viewDir);
            
                    vec3 ambient = u_LightingData[i].intensity * u_LightingData[i].color;
                    vec3 diffuse = max(dot(v_Normal, lightDir), 0.0) * u_LightingData[i].color / max(0.1, distance);
                    vec3 specular = pow(max(0.0, dot(v_Normal, halfDir)), 2.0) * u_LightingData[i].color;
            
                    diffuse  *= attenuation;
                    specular *= attenuation;
            
                    result += ambient + diffuse + specular;
                }
            
                // Apply gamma.
                result = pow(result, vec3(1.0 / u_Gamma));
            
                o_Color = vec4(result, 1.0) * v_Color;
            }
            )"
        },
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
