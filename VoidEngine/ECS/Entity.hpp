#ifndef VOID_ECS_ENTITY_H__
#define VOID_ECS_ENTITY_H__

#include <map>
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
        std::map<std::type_index, Component *> m_Components;

    public:
        std::string name = "Void Entity";

        Vector3 position = Vector3(0, 0, 0);
        Vector3 rotation = Vector3(0, 0, 0);
        Vector3 scale    = Vector3(1, 1, 1);

        bool isStatic = false;
        bool renderable = true;

        Entity();
        Entity(std::string);
        ~Entity();

        void LookAt(Vector3);

        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}

        template<typename T>
        T *AddComponent();

        template<typename T>
        T *GetComponent();

        template<typename T>
        void DestroyComponent();

        Vector3 Up();
        Vector3 Forward();
        Vector3 Right();
    };
};

/**
 *  TEMPLATE IMPLEMENTATIONS
 */
namespace VOID_NS {
    template<class T>
    T *Entity::AddComponent() {
        std::type_index tindex = std::type_index(typeid(T));

        static_assert(std::is_base_of<Component, T>(), "Can't add component: component is not derived from Void::Component");

        T *c = new T();

        if(((Component *) c)->m_SingleComponent) {
            for(auto c_ : this->m_Components) {
                if(c_.first == tindex) {
                    Logger::Error("Can't add ", Logger::GetClassName<T>(), " to ", this->name, ": component already exists");
                    return NULL;
                }
            }
        }

        ((Component *) c)->m_GameObject = this;
        this->m_Components.emplace(std::make_pair(tindex, (Component *) c));
        return c;
    }

    template<class T>
    T *Entity::GetComponent() {
        std::type_index tindex = std::type_index(typeid(T));

        static_assert(std::is_base_of<Component, T>(), "Can't add component: component is not derived from Void::Component");

        for(auto c_ : this->m_Components) {
            if(c_.first == tindex) {
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
        for(auto c_ : this->m_Components) {
            if(c_.first == tindex) {
                this->m_Components.erase(tindex);
                return;
            }
            i++;
        }
    }
};

#endif /* VOID_ECS_ENTITY_H__ */
