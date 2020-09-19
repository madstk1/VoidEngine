#ifndef VOID_SHADER_DEFAULT_H__
#define VOID_SHADER_DEFAULT_H__

ShaderCreationInfo k_ShaderDefault = {
    "Default",
    GLSLVersion::V450, GLSLProfile::Core, {
        { ShaderStage::Vertex, R"(
            struct vs_Uniform {
                mat4 u_Model;
                mat4 u_View;
                mat4 u_Projection;
            };

            /* Input variables. */
            layout(location = 0) in vec3 i_Position;
            layout(location = 1) in vec3 i_Normal;
            layout(location = 2) in vec2 i_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec3 v_Position;
            layout(location = 1) out vec3 v_Normal;
            layout(location = 2) out vec2 v_TexCoords;
            
            /* Uniform variables. */
            uniform vs_Uniform vs_Void;
            
            void main() {
                gl_Position = vs_Void.u_Projection * vs_Void.u_View * vs_Void.u_Model * vec4(i_Position, 1.0);
                v_Position  = vec3(vs_Void.u_Model * vec4(i_Position, 1.0));
                v_Normal    = i_Normal * mat3(vs_Void.u_Model);
                v_TexCoords = i_TexCoords;
            }
        )"},
        { ShaderStage::Fragment, R"(
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

            const float PI = 3.14159265359;
            
            /* Input variables. */
            layout(location = 0) in vec3 v_Position;
            layout(location = 1) in vec3 v_Normal;
            layout(location = 2) in vec2 v_TexCoords;
            
            /* Output variables. */
            layout(location = 0) out vec4 o_Color;
            
            /* Uniform variables. */
            uniform fs_Uniform  fs_Void;
            uniform fs_Material fs_Mat;

            vec3 Fresnel(float theta, vec3 F) {
                return F + (1.0 - F) * pow(1.0 - theta, 5.0);
            }

            float DistributionGGX(vec3 N, vec3 H, float roughness) {
                float a   = pow(roughness, 2.0);
                float a2  = pow(a, 2.0);
                float NH  = max(dot(N, H), 0.0);
                float NH2 = pow(NH, 2.0);

                float den = (NH2 * (a2 - 1.0) + 1.0);
                den = PI * den * den;

                return a2 / den;
            }

            float SchlickGGX(float NV, float roughness) {
                float r = roughness + 1.0;
                float k = pow(r, 2.0) / 8.0;

                return (NV) / (NV * (1.0 - k) + k);
            }

            float SmithGGX(vec3 N, vec3 V, vec3 L, float roughness) {
                float NV = max(dot(N, V), 0.0);
                float NL = max(dot(N, L), 0.0);
                
                return SchlickGGX(NV, roughness) * SchlickGGX(NL, roughness);
            }

            vec3 CalculateLight(PointLight light, vec3 N, vec3 V, vec3 F0) {
                vec3 L = normalize(light.position - v_Position);
                vec3 H = normalize(V + L);

                float distance = length(light.position - v_Position);
                float attenuation = 1.0 / distance;
                vec3  radiance = light.color.rgb * attenuation;
                vec3  F = Fresnel(max(dot(H, V), 0.0), F0);

                float NDF = DistributionGGX(N, H, fs_Mat.u_Roughness);
                float G   = SmithGGX(N, V, L, fs_Mat.u_Roughness);

                /* Cook-Torrance BRDF */
                vec3 num = NDF * G * F;
                float de = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
                vec3 spec = num / max(de, 0.001);

                vec3 kS = F;
                vec3 kD = (vec3(1.0) - kS) * (1.0 - fs_Mat.u_Metallic);

                float NL = max(dot(N, L), 0.0);
            
                return (kD * fs_Mat.u_Albedo.rgb / PI + spec) * radiance * NL;
            }
            
            void main() {
                vec3 Lo = vec3(0.0);

                vec3 N = normalize(v_Normal);
                vec3 V = normalize(fs_Void.u_CameraPosition - v_Position);
                vec3 F0 = mix(vec3(0.04), fs_Mat.u_Albedo.rgb, fs_Mat.u_Metallic);

                for(uint i = 0; i < fs_Void.u_LightCount; i++) {
                    Lo += CalculateLight(fs_Void.u_LightingData[i], N, V, F0);
                }

                // Apply ambient light.
                Lo += vec3(0.03) * fs_Mat.u_Albedo.rgb * fs_Mat.u_Occlusion;
            
                // Apply gamma.
                Lo = Lo / (Lo + vec3(1.0));
                Lo = Lo * fs_Void.u_Gamma;

                o_Color = vec4(Lo, 1.0);
            }
        )"},
    }, {
        sizeof(Vertex), {
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, position) },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, normal)   },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L2D, false, offsetof(Vertex, texCoords) },
        }
    }
};

#endif /* VOID_SHADER_DEFAULT_H__ */
