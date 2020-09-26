#pragma once

#include <vector>
#include <fstream>
#include <algorithm>

#include <VoidEngine/Core/Common.hpp>

#include <glslang/Public/ShaderLang.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/Include/ResourceLimits.h>

using namespace glslang;

namespace VOID_NS {
    const TBuiltInResource GetResources() {
        const TLimits DefaultTLimits = {
            .nonInductiveForLoops = 1,
            .whileLoops = 1,
            .doWhileLoops = 1,
            .generalUniformIndexing = 1,
            .generalAttributeMatrixVectorIndexing = 1,
            .generalVaryingIndexing = 1,
            .generalSamplerIndexing = 1,
            .generalVariableIndexing = 1,
            .generalConstantMatrixVectorIndexing = 1,
        };
    
        TBuiltInResource DefaultTBuiltInResource = {
            .maxLights = 32,
            .maxClipPlanes = 6,
            .maxTextureUnits = 32,
            .maxTextureCoords = 32,
            .maxVertexAttribs = 64,
            .maxVertexUniformComponents = 4096,
            .maxVaryingFloats = 64,
            .maxVertexTextureImageUnits = 32,
            .maxCombinedTextureImageUnits = 80,
            .maxTextureImageUnits = 32,
            .maxFragmentUniformComponents = 4096,
            .maxDrawBuffers = 32,
            .maxVertexUniformVectors = 128,
            .maxVaryingVectors = 8,
            .maxFragmentUniformVectors = 16,
            .maxVertexOutputVectors = 16,
            .maxFragmentInputVectors = 15,
            .minProgramTexelOffset = -8,
            .maxProgramTexelOffset = 7,
            .maxClipDistances = 8,
            .maxComputeWorkGroupCountX = 65535,
            .maxComputeWorkGroupCountY = 65535,
            .maxComputeWorkGroupCountZ = 65535,
            .maxComputeWorkGroupSizeX = 1024,
            .maxComputeWorkGroupSizeY = 1024,
            .maxComputeWorkGroupSizeZ = 64,
            .maxComputeUniformComponents = 1024,
            .maxComputeTextureImageUnits = 16,
            .maxComputeImageUniforms = 8,
            .maxComputeAtomicCounters = 8,
            .maxComputeAtomicCounterBuffers = 1,
            .maxVaryingComponents = 60,
            .maxVertexOutputComponents = 64,
            .maxGeometryInputComponents = 64,
            .maxGeometryOutputComponents = 128,
            .maxFragmentInputComponents = 128,
            .maxImageUnits = 8,
            .maxCombinedImageUnitsAndFragmentOutputs = 8,
            .maxCombinedShaderOutputResources = 8,
            .maxImageSamples = 0,
            .maxVertexImageUniforms = 0,
            .maxTessControlImageUniforms = 0,
            .maxTessEvaluationImageUniforms = 0,
            .maxGeometryImageUniforms = 0,
            .maxFragmentImageUniforms = 8,
            .maxCombinedImageUniforms = 8,
            .maxGeometryTextureImageUnits = 16,
            .maxGeometryOutputVertices = 256,
            .maxGeometryTotalOutputComponents = 1024,
            .maxGeometryUniformComponents = 1024,
            .maxGeometryVaryingComponents = 64,
            .maxTessControlInputComponents = 128,
            .maxTessControlOutputComponents = 128,
            .maxTessControlTextureImageUnits = 16,
            .maxTessControlUniformComponents = 1024,
            .maxTessControlTotalOutputComponents = 4096,
            .maxTessEvaluationInputComponents = 128,
            .maxTessEvaluationOutputComponents = 128,
            .maxTessEvaluationTextureImageUnits = 16,
            .maxTessEvaluationUniformComponents = 1024,
            .maxTessPatchComponents = 120,
            .maxPatchVertices = 32,
            .maxTessGenLevel = 64,
            .maxViewports = 16,
            .maxVertexAtomicCounters = 0,
            .maxTessControlAtomicCounters = 0,
            .maxTessEvaluationAtomicCounters = 0,
            .maxGeometryAtomicCounters = 0,
            .maxFragmentAtomicCounters = 8,
            .maxCombinedAtomicCounters = 8,
            .maxAtomicCounterBindings = 1,
            .maxVertexAtomicCounterBuffers = 0,
            .maxTessControlAtomicCounterBuffers = 0,
            .maxTessEvaluationAtomicCounterBuffers = 0,
            .maxGeometryAtomicCounterBuffers = 0,
            .maxFragmentAtomicCounterBuffers = 1,
            .maxCombinedAtomicCounterBuffers = 1,
            .maxAtomicCounterBufferSize = 16384,
            .maxTransformFeedbackBuffers = 4,
            .maxTransformFeedbackInterleavedComponents = 64,
            .maxCullDistances = 8,
            .maxCombinedClipAndCullDistances = 8,
            .maxSamples = 4,
            .maxMeshOutputVerticesNV = 256,
            .maxMeshOutputPrimitivesNV = 512,
            .maxMeshWorkGroupSizeX_NV = 32,
            .maxMeshWorkGroupSizeY_NV = 1,
            .maxMeshWorkGroupSizeZ_NV = 1,
            .maxTaskWorkGroupSizeX_NV = 32,
            .maxTaskWorkGroupSizeY_NV = 1,
            .maxTaskWorkGroupSizeZ_NV = 1,
            .maxMeshViewCountNV = 4,
        };
    
        DefaultTBuiltInResource.limits = DefaultTLimits;
    
        return DefaultTBuiltInResource;
    }

    class DirStackFileIncluder : public glslang::TShader::Includer {
    public:
        DirStackFileIncluder() : externalLocalDirectoryCount(0) { }
    
        virtual IncludeResult* includeLocal(const char* headerName, const char* includerName, size_t inclusionDepth) override {
            return readLocalPath(headerName, includerName, (int)inclusionDepth);
        }
    
        virtual IncludeResult* includeSystem(const char *headerName, const char *, size_t) override {
            return readSystemPath(headerName);
        }
    
        virtual void pushExternalLocalDirectory(const std::string& dir) {
            directoryStack.push_back(dir);
            externalLocalDirectoryCount = (int)directoryStack.size();
        }
    
        virtual void releaseInclude(IncludeResult* result) override {
            if (result != nullptr) {
                delete [] static_cast<tUserDataElement*>(result->userData);
                delete result;
            }
        }
    
        virtual ~DirStackFileIncluder() override { }
    
    protected:
        typedef char tUserDataElement;
        std::vector<std::string> directoryStack;
        int externalLocalDirectoryCount;
    
        virtual IncludeResult* readLocalPath(const char* headerName, const char* includerName, int depth) {
            directoryStack.resize(depth + externalLocalDirectoryCount);
            if (depth == 1)
                directoryStack.back() = getDirectory(includerName);
    
            for (auto it = directoryStack.rbegin(); it != directoryStack.rend(); ++it) {
                std::string path = *it + '/' + headerName;
                std::replace(path.begin(), path.end(), '\\', '/');
                std::ifstream file(path, std::ios_base::binary | std::ios_base::ate);
                if (file) {
                    directoryStack.push_back(getDirectory(path));
                    return newIncludeResult(path, file, (int)file.tellg());
                }
            }
            return nullptr;
        }
    
        virtual IncludeResult *readSystemPath(const char *) const {
            return nullptr;
        }
    
        virtual IncludeResult *newIncludeResult(const std::string &path, std::ifstream &file, int length) const {
            char* content = new tUserDataElement [length];
            file.seekg(0, file.beg);
            file.read(content, length);
            return new IncludeResult(path, content, length, content);
        }
    
        virtual std::string getDirectory(const std::string path) const {
            size_t last = path.find_last_of("/\\");
            return last == std::string::npos ? "." : path.substr(0, last);
        }
    };
};
