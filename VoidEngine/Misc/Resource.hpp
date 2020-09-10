#ifndef VOID_MISC_RESOURCE_H__
#define VOID_MISC_RESOURCE_H__

#include <vector>

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class Resource {
    public:
        typedef enum {
            Unknown  = (u32) 0,
            Shader,
            Texture,
        } Type;

        Resource(std::string, Type);
        ~Resource();

    protected:
        std::string m_Name;
        Type m_Type;
    };

    class ResourceMap {
    private:
    protected:
        typedef struct {
            std::string name;
            Resource::Type type;

            Resource *resc;
        } _IntResource;

        std::vector<_IntResource> m_Resources;

    public:
        ResourceMap() {}
        ~ResourceMap() = default;

        void push(std::string, Resource::Type, Resource *);
        Resource *erase(std::string, Resource::Type);
        const Resource *find(std::string, Resource::Type) const;
    };

    class ResourceManager {
        friend Resource;

    private:
        ResourceManager() {}
        ~ResourceManager() {}

    protected:
        static ResourceMap m_Resources;

    public:
        const Resource *GetResource(std::string name, Resource::Type type) const {
            return m_Resources.find(name, type);
        }
    };
};

#endif /* VOID_MISC_RESOURCE_H__ */
