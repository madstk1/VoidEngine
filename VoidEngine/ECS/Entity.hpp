#ifndef VOID_ECS_ENTITY_H__
#define VOID_ECS_ENTITY_H__

#include <vector>
#include <utility>
#include <typeindex>
#include <type_traits>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class Entity {
    private:
    protected:
        std::vector<std::pair<std::type_index, Component *>> m_Components;

    public:
        std::string name = "Void Entity";

        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 rotation = glm::vec3(0, 0, 0);

        bool isStatic = false;
        bool renderable = false;

        Entity();
        Entity(std::string);
        ~Entity();

        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}

        template<typename T>
        T *AddComponent(T *comp);

        template<typename T>
        T *GetComponent();

        template<typename T>
        void DestroyComponent();
    };
};

/**
 *  TEMPLATE IMPLEMENTATIONS
 */
namespace VOID_NS {
    template<class T>
    T *Entity::AddComponent(T *comp) {
        std::type_index tindex = std::type_index(typeid(*comp));

        static_assert(std::is_base_of<Component, T>(), "Can't add component: component is not derived from Void::Component");

        for(std::pair<std::type_index, Component *> &c_ : this->m_Components) {
            if(c_.first.name() == tindex.name()) {
                Logger::LogError("Can't add %s to %s: component already exists", Logger::GetClassName<T>(), this->name.c_str());
                return NULL;
            }
        }

        Component *c = (Component *) comp;
        c->m_GameObject = this;

        this->m_Components.push_back(std::make_pair(tindex, c));
        Logger::LogInfo("Added component of type %s to %s.", Logger::GetClassName<T>(), this->name.c_str());

        return comp;
    }

    template<class T>
    T *Entity::GetComponent() {
        std::type_index tindex = std::type_index(typeid(T));

        static_assert(std::is_base_of<Component, T>(), "Can't add component: component is not derived from Void::Component");

        for(std::pair<std::type_index, Component *> &c_ : this->m_Components) {
            if(c_.first.name() == tindex.name()) {
                return (T *) c_.second;
            }
        }
        return nullptr;
    }

    template<class T>
    void Entity::DestroyComponent() {
        std::type_index tindex = std::type_index(typeid(T));

        static_assert(std::is_base_of<Component, T>(), "Can't add component: component is not derived from Void::Component");

        u32 i = 0;
        for(std::pair<std::type_index, Component *> &c_ : this->m_Components) {
            if(c_.first.name() == tindex.name()) {
                this->m_Components.erase(this->m_Components.begin() + i);
                Logger::LogInfo("Removed component of type %s from %s.", Logger::GetClassName<T>(), this->name.c_str());
                return;
            }
            i++;
        }
    }
};

#endif /* VOID_ECS_ENTITY_H__ */
