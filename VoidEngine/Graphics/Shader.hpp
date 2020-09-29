#pragma once

#include <map>
#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Graphics/RendererTypes.hpp>

namespace VOID_NS {
    /**
     *  Struct used to create a shader, including name, source, etc.
     */
    struct ShaderCreationInfo {
        /**
         *  Since both Vulkan and OpenGL needs to be supported,
         *  the source is supplied in both SPIR-V and GLSL.
         */
        struct Source {
            std::vector<u32> assembly;
            string human;
        };

        /**
         *  Name of the to-be shader.
         */
        string name;

        /**
         *  Version of the shader.
         *  This is defined using GLSL versions.
         */
        ShaderVersion version;

        /**
         *  Profile of the shader.
         *  This is defined using GLSL profiles.
         */
        ShaderProfile profile;

        /**
         *  Shader map, containing the sources for each stage.
         */
        std::map<ShaderStage, Source> sources;

        /**
         *  Constructor for all members.
         */
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

    /**
     *  Shader object.
     *
     *  It is generally not recommended to create shaders yourself.
     *  Instead, use the renderer to automate the process.
     */
    class Shader {
    public:
        /**
         *  Constructor, using only the name.
         */
        Shader(string name)
            : m_Name(name) {}

        /**
         *  Constructor, using name and version.
         */
        Shader(
            string name,
            ShaderVersion version
        ) : m_Name(name), m_Version(version) {}

        /**
         *  Constructor, using name, version and profile.
         */
        Shader(
            string name,
            ShaderVersion version,
            ShaderProfile profile
        ) : m_Name(name), m_Version(version), m_Profile(profile) {}

        /**
         *  Query methods.
         */
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
