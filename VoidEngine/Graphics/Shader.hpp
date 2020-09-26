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

        inline const ShaderID GetID() const { return m_ID; }
        inline const string GetName() const { return m_Name; }
        inline const ShaderVersion GetVersion() const { return m_Version; }
        inline const ShaderProfile GetProfile() const { return m_Profile; }

    protected:
        Shader() = delete;

        ShaderID m_ID;

        string m_Name;
        ShaderVersion m_Version = ShaderVersion::V450;
        ShaderProfile m_Profile = ShaderProfile::Core;
    };
};
