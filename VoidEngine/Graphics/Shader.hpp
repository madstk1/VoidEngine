#pragma once

#include <map>
#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Graphics/RendererTypes.hpp>

namespace VOID_NS {
    struct ShaderCreationInfo {
        struct Source {
            std::vector<u32> assembly;
            string human;
        };

        string name;
        ShaderVersion version;
        ShaderProfile profile;

        std::map<ShaderStage, Source> sources;

        ShaderCreationInfo(string name, ShaderVersion version, ShaderProfile profile, std::map<ShaderStage, string> sources) {
            this->name = name;
            this->version = version;
            this->profile = profile;
            
            for(const auto &s : sources) {
                Source src = {{}, s.second};
                this->sources.emplace(s.first, src);
            }
        }
    };

    class Shader {
    public:
        Shader(string name)
            : m_Name(name) {}

        Shader(
            string name,
            ShaderVersion version
        ) : m_Name(name), m_Version(version) {}

        Shader(
            string name,
            ShaderVersion version,
            ShaderProfile profile
        ) : m_Name(name), m_Version(version), m_Profile(profile) {}

        inline ShaderID GetID() const { return m_ID; }
        inline const string GetName() const { return m_Name; }
        inline ShaderVersion GetVersion() const { return m_Version; }
        inline ShaderProfile GetProfile() const { return m_Profile; }

    protected:
        Shader() = delete;

        ShaderID m_ID;

        string m_Name;
        ShaderVersion m_Version = ShaderVersion::V450;
        ShaderProfile m_Profile = ShaderProfile::Core;
    };
};
