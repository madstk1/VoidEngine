#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Resource.hpp>

namespace VOID_NS {
    ResourceMap ResourceManager::m_Resources;

    /**
     *  Resource
     */

    Resource::Resource(std::string name, Type type) {
        m_Name = name;
        m_Type = type;
        ResourceManager::m_Resources.push(name, type, this);
    }

    Resource::~Resource() {
        ResourceManager::m_Resources.erase(m_Name, m_Type);
    }

    /**
     *  Resource Map
     */

    void ResourceMap::push(std::string name, Resource::Type type, Resource *resc) {
        if(find(name, type) != nullptr) {
            Logger::LogError("Resource(%s, %d) already exists in resource map.", name.c_str(), type);
            return;
        }
        m_Resources.push_back({name, type, resc});

        Logger::LogDebug(
            "Added Resource {%s, %d} to resource map.",
            name.c_str(), 
            type
        );
    }

    Resource *ResourceMap::erase(std::string name, Resource::Type type) {
        u32 i = 0;
        for(const _IntResource &ir : m_Resources) {
            if(ir.name == name && ir.type == type) {
                Logger::LogDebug(
                    "Remove Resource {%s, %d} to resource map.",
                    name.c_str(), 
                    type
                );

                m_Resources.erase(m_Resources.begin() + i);
                return m_Resources[i].resc;
            }
            i++;
        }
        Logger::LogError("Resource(%s, %d) doesn't exist in resource map.", name.c_str(), type);
        return nullptr;
    }

    const Resource *ResourceMap::find(std::string name, Resource::Type type) const {
        for(const _IntResource &ir : m_Resources) {
            if(ir.type == type && ir.name == name) {
                return ir.resc;
            }
        }
        return nullptr;
    }

    const std::vector<Resource *> ResourceMap::get_type(Resource::Type type) const {
        std::vector<Resource *> resources;

        for(const _IntResource &ir : m_Resources) {
            if(ir.type == type) {
                resources.push_back(ir.resc);
            }
        }
        return resources;
    }
};
