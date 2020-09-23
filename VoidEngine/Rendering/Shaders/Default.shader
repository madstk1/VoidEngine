#ifndef VOID_SHADER_DEFAULT_H__
#define VOID_SHADER_DEFAULT_H__

ShaderCreationInfo k_ShaderDefault = {
    "Default",
    GLSLVersion::V450, GLSLProfile::Core, {
        { ShaderStage::Vertex, R"(
            void main() {
                gl_Position = ub_MVP.Projection * ub_MVP.View * ub_MVP.Model * vec4(i_Position, 1.0);
                o_Position  = vec3(ub_MVP.Model * vec4(i_Position, 1.0));
                o_Normal    = i_Normal * mat3(ub_MVP.Model);
                o_TexCoords = i_TexCoords;
            }
        )"},
        { ShaderStage::Fragment, R"(
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
                vec3 L = normalize(light.Position - i_Position);
                vec3 H = normalize(V + L);

                float distance = length(light.Position - i_Position);
                float attenuation = 1.0 / distance;
                vec3  radiance = light.Color.rgb * attenuation;
                vec3  F = Fresnel(max(dot(H, V), 0.0), F0);

                float NDF = DistributionGGX(N, H, ub_Material.Roughness);
                float G   = SmithGGX(N, V, L, ub_Material.Roughness);

                /* Cook-Torrance BRDF */
                vec3 num = NDF * G * F;
                float de = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
                vec3 spec = num / max(de, 0.001);

                vec3 kS = F;
                vec3 kD = (vec3(1.0) - kS) * (1.0 - ub_Material.Metallic);

                float NL = max(dot(N, L), 0.0);
            
                return (kD * ub_Material.Albedo.rgb / PI + spec) * radiance * NL;
            }
            
            void main() {
                vec3 Lo = vec3(0.0);

                vec3 N = normalize(i_Normal);
                vec3 V = normalize(ub_Light.CameraPosition - i_Position);
                vec3 F0 = mix(vec3(0.04), ub_Material.Albedo.rgb, ub_Material.Metallic);

                for(uint i = 0; i < ub_Light.LightCount; i++) {
                    Lo += CalculateLight(ub_Light.LightingData[i], N, V, F0);
                }

                // Apply ambient light.
                Lo += vec3(0.03) * ub_Material.Albedo.rgb * ub_Material.Occlusion;
            
                // Apply gamma.
                Lo = Lo / (Lo + vec3(1.0));
                Lo = Lo * ub_Light.Gamma;

                o_Color = vec4(Lo, 1.0);
            }
        )"},
    }
};

#endif /* VOID_SHADER_DEFAULT_H__ */
