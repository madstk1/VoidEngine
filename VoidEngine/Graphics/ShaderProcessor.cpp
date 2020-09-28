#include <glslang/Public/ShaderLang.h>
#include <glslang/Include/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <glslang/SPIRV/Logger.h>
#include <glslang/SPIRV/SpvTools.h>

#include <spirv_cross/spirv.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Engine.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Misc/Translations.hpp>
#include <VoidEngine/Memory/Allocator.hpp>
#include <VoidEngine/Graphics/Renderer.hpp>
#include <VoidEngine/Graphics/Shader.hpp>
#include <VoidEngine/Graphics/ShaderProcessor.hpp>
#include <VoidEngine/Graphics/glslang.hpp>

namespace VOID_NS {
    /**
     *  Default shaders.
     */

    #include "../Resources/Shaders/Default.shader"
    #include "../Resources/Shaders/Framebuffer.shader"
    #include "../Resources/Shaders/Skybox.shader"
};

namespace VOID_NS {
    inline EShLanguage Translate(ShaderStage e) {
        switch(e) {
            case ShaderStage::Vertex:                return EShLangVertex;
            case ShaderStage::Fragment:              return EShLangFragment;
            case ShaderStage::Compute:               return EShLangCompute;
            case ShaderStage::Geometry:              return EShLangGeometry;
            case ShaderStage::TesselationControl:    return EShLangTessControl;
            case ShaderStage::TesselationEvaluation: return EShLangTessEvaluation;
            
            default: break;
        }
        return EShLangCount;
    }

    void ShaderProcessor::Initialize() {
        glslang::InitializeProcess();

        /**
         *  Compile default shaders.
         */

        RenderingAPI api = Engine::Get()->GetAPI();
        ProcessShader(k_ShaderDefault,     api);
        ProcessShader(k_ShaderFramebuffer, api);
        ProcessShader(k_ShaderSkybox,      api);
    }

    void ShaderProcessor::Destroy() {
        glslang::FinalizeProcess();
    }

    void ShaderProcessor::ProcessShader(ShaderCreationInfo *info, RenderingAPI api) {
        Logger::Assert(info != nullptr, "Inputted ShaderCreationInfo is null.");
        Logger::Assert(info->name != "", "ShaderCreationInfo has no name.");
        Logger::Assert(info->sources.size() > 0, "ShaderCreationInfo has no sources.");

        /**
         *  Compile to SPIRV
         */

        glslang::TProgram *program = new glslang::TProgram();
        Vector<u32> spirvBinary;
        spv::SpvBuildLogger spvLogger;
        SpvOptions spvOptions;

        const EShMessages msg = EShMsgDefault;
        const TBuiltInResource resources = GetResources();
        DirStackFileIncluder includer;

        for(auto &src : info->sources) {
            glslang::TShader *shader = new glslang::TShader(Translate(src.first));

            src.second.human =
                "#version " +
                Translator::TranslateString(info->version) + " " + 
                Translator::TranslateString(info->profile) +
                "\n" +

                GetDefaultGLSLInclude() +
                GetDefaultStageInclude(src.first) +
                src.second.human;

            const char *sourceStr = src.second.human.c_str();
            const int sourceLength = strlen(sourceStr);
            const char *shaderName = info->name.c_str();

            shader->setStringsWithLengthsAndNames(&sourceStr, &sourceLength, &shaderName, 1);
            shader->setAutoMapBindings(true);
            shader->setAutoMapLocations(true);

            shader->setEnvClient(glslang::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
            shader->setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_4);
            shader->setEnvInput(glslang::EShSource::EShSourceGlsl, Translate(src.first), glslang::EShClient::EShClientVulkan, 110);

            if(!shader->parse(&resources, 110, false, msg, includer)) {
                Logger::Warning("Source:\n", sourceStr);
                Logger::Fatal("Failed to compile shader ", info->name, " (", Translator::TranslateString(src.first), "): ", shader->getInfoLog());
            }

            program->addShader(shader);
        }

        if(!program->link(msg)) {
            Logger::Fatal("Failed to link program:\n", info->name, ": ", program->getInfoLog());
        }

        spvOptions.generateDebugInfo = VOID_ENABLE_DEBUG_FLAG;
        spvOptions.disableOptimizer = VOID_ENABLE_DEBUG_FLAG;
        spvOptions.optimizeSize = !(VOID_ENABLE_DEBUG_FLAG);
        spvOptions.validate = true;

        for(auto &src : info->sources) {
            glslang::TIntermediate *inter = program->getIntermediate(Translate(src.first));
            glslang::GlslangToSpv(*inter, src.second.assembly, &spvLogger, &spvOptions);

            Logger::Assert(src.second.assembly.size() > 0, "Outputted size of SPIRV is zero.");
        }

        /* If SPIR-V is desired, return here. */
        if(api == RenderingAPI::Vulkan) {
            return;
        }

        /**
         *  Translate into GLSL.
         */

        spirv_cross::CompilerGLSL *compiler;
        spirv_cross::CompilerGLSL::Options spirvOptions;

        spirvOptions.es = false;
        spirvOptions.version = 450;
        spirvOptions.enable_420pack_extension = true;
        spirvOptions.flatten_multidimensional_arrays = true;

        for(auto &src : info->sources) {
            compiler = Allocator::Allocate<spirv_cross::CompilerGLSL>(std::move(src.second.assembly));
            compiler->set_common_options(spirvOptions);

            src.second.human = compiler->compile();

            Allocator::Free(compiler);
        }

        Logger::Info("Finished compiling shader ", info->name);
    }

    string ShaderProcessor::GetDefaultGLSLInclude() {
        return R"(
            /**
             *  In/out attributes
             */

            in vec3 i_Position;
            in vec3 i_Normal;
            in vec2 i_TexCoords;

            out vec3 o_Position;
            out vec3 o_Normal;
            out vec2 o_TexCoords;

            /**
             *  Generic struct definitions
             */

            struct PointLight {
                vec4 Color;
                vec3 Position;
                float Intensity;
            };

            /**
             *  Uniform block definitions
             */

            uniform vd_ub_Material {
                vec4  Albedo;
                float Metallic;
                float Roughness;
                float Occlusion;
            } ub_Material;

            uniform vd_ub_MVP {
                mat4 Model;
                mat4 View;
                mat4 Projection;
            } ub_MVP;

            uniform vd_ub_Light {
                float      Gamma;
                vec3       CameraPosition;
                uint       LightCount;
                PointLight LightingData[32];
            } ub_Light;

            uniform samplerCube ub_Skybox;
            uniform sampler2D ub_Framebuffer;

            /**
             *  Constants
             */

            const float PI = 3.14159265359;

            /**
             *  Common functions
             */

            vec3 Fresnel(float theta, vec3 F) {
                return F + (1.0 - F) * pow(1.0 - theta, 5.0);
            }

            vec4 Fresnel(float theta, vec4 F) {
                return F + (1.0 - F) * pow(1.0 - theta, 5.0);
            }

            float NormalDistribution(vec3 N, vec3 H, float roughness) {
                float a2  = pow(pow(roughness, 2.0), 2.0);
                float NH  = max(dot(N, H), 0.0);
                float NH2 = pow(NH, 2.0);

                float den = (NH2 * (a2 - 1.0) + 1.0);
                den = PI * den * den;

                return a2 / den;
            }

            float SchlickBeckmann(float NV, float roughness) {
                float k = pow(roughness + 1.0, 2.0) * 0.125;
                return NV / (NV * (1.0 - k) + k);
            }

            float SmithGGX(vec3 N, vec3 V, vec3 L, float roughness) {
                float NV = max(dot(N, V), 0.0);
                float NL = max(dot(N, L), 0.0);

                return SchlickBeckmann(NV, roughness) * SchlickBeckmann(NL, roughness);
            }
        )";
    }

    string ShaderProcessor::GetDefaultStageInclude(ShaderStage e) {
        std::map<ShaderStage, string> includes = {
            { ShaderStage::Vertex,                  "" },
            { ShaderStage::Fragment,                R"(
                out vec4 o_Color;
            )" },
            { ShaderStage::Geometry,                "" },
            { ShaderStage::Compute,                 "" },
            { ShaderStage::TesselationControl,      "" },
            { ShaderStage::TesselationEvaluation,   "" },
        };
        return includes[e];
    }
};
