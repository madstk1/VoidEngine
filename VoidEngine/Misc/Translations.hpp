#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Graphics/RendererTypes.hpp>

namespace VOID_NS {
    class Translator {
    public:
        static inline string TranslateString(Error e) {
            switch(e) {
                case Error::NoError:          return "No error.";
                case Error::InvalidAPI:       return "Unsupported or unknown rendering API.";
                case Error::ErrorAllocation:  return "Failed to allocate memory.";
                case Error::NullPointer:      return "Passed value is nullptr.";
                case Error::InvalidEnum:      return "Invalid enum.";
            }
            return TranslateString(Error::InvalidEnum);
        }

        static inline string TranslateString(ShaderStage e) {
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

        static inline string TranslateString(ShaderVersion e) {
            switch(e) {
                case ShaderVersion::V420: return "420";
                case ShaderVersion::V430: return "430";
                case ShaderVersion::V440: return "440";
                case ShaderVersion::V450: return "450";
                case ShaderVersion::V460: return "460";
            }
            Logger::Assert(false, TranslateString(Error::InvalidEnum));
            return "";
        }

        static inline string TranslateString(ShaderProfile e) {
            switch(e) {
                case ShaderProfile::Core:          return "core";
                case ShaderProfile::Compatibility: return "compatibility";
            }
            Logger::Assert(false, TranslateString(Error::InvalidEnum));
            return "";
        }
    };
};
