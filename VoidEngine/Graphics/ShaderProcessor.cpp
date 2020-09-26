#include <glslang/Public/ShaderLang.h>
#include <glslang/Include/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <glslang/SPIRV/Logger.h>
#include <glslang/SPIRV/SpvTools.h>

#include <spirv_cross/spirv.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Memory/Allocator.hpp>
#include <VoidEngine/Graphics/Shader.hpp>
#include <VoidEngine/Graphics/ShaderProcessor.hpp>
#include <VoidEngine/Graphics/glslang.hpp>

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

    string ShaderProcessor::TranslateString(ShaderStage e) {
        switch(e) {
            case ShaderStage::Vertex:                return "Vertex";
            case ShaderStage::Fragment:              return "Fragment";
            case ShaderStage::Compute:               return "Compute";
            case ShaderStage::Geometry:              return "Geometry";
            case ShaderStage::TesselationControl:    return "TessControl";
            case ShaderStage::TesselationEvaluation: return "TessEvaluation";
            
            default: break;
        }
        return "INVALID";
    }

    void ShaderProcessor::Initialize() {
        glslang::InitializeProcess();
    }

    void ShaderProcessor::Destroy() {
        glslang::FinalizeProcess();
    }

    void ShaderProcessor::ProcessShader(ShaderCreationInfo *info, RenderingAPI api) {
        Logger::Assert(info != nullptr, "Inputted ShaderCreationInfo is null.");
        Logger::Assert(info->name == "", "ShaderCreationInfo has no name.");
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

            const char *sourceStr = src.second.human.c_str();
            const int sourceLength = strlen(sourceStr);
            const char *shaderName = info->name.c_str();

            shader->setStringsWithLengthsAndNames(&sourceStr, &sourceLength, &shaderName, 1);
            shader->setSourceEntryPoint("main");
            shader->setAutoMapBindings(true);
            shader->setAutoMapLocations(true);

            shader->setEnvClient(glslang::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
            shader->setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_4);
            shader->setEnvInput(glslang::EShSource::EShSourceGlsl, Translate(src.first), glslang::EShClient::EShClientVulkan, 110);

            if(!shader->parse(&resources, 110, false, msg, includer)) {
                Logger::Fatal("Failed to compile shader ", info->name, " (", TranslateString(src.first), "): ", shader->getInfoLog());
            }

            program->addShader(shader);
        }

        if(!program->link(msg)) {
            Logger::Fatal("Failed to link program ", info->name, ": ", program->getInfoLog());
        }

        spvOptions.generateDebugInfo = VOID_ENABLE_DEBUG_FLAG;
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
    }
};
