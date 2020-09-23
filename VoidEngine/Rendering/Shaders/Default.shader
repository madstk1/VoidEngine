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
            vec3 CalculateLight(PointLight light, vec3 N, vec3 V, vec3 F0) {
                vec3 L = normalize(light.Position - i_Position);
                vec3 H = normalize(V + L);

                float distance = length(light.Position - i_Position);
                float attenuation = 1.0 / distance;
                vec3  radiance = light.Color.rgb * attenuation;
                vec3  F = Fresnel(max(dot(H, V), 0.0), F0);

                float NDF = NormalDistribution(N, H, ub_Material.Roughness);
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

                // Apply skybox reflection
                vec3 I = normalize(i_Position - ub_Light.CameraPosition);
                vec3 R = reflect(I, N);

                Lo += ub_Material.Metallic * texture(ub_Skybox.Skybox, R).rgb;

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
