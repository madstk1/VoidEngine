#pragma once

#include <map>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Transform.hpp>

namespace VOID_NS {
    class Entity {
    protected:
        std::map<std::type_index, Component *> m_Components;

    public:
        string name = "Void Entity";
        bool enabled = true;

        Transform transform;

        Entity();
        Entity(string);
        ~Entity();

        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}

        template<typename T, typename ... Args>
        T *AddComponent(Args ... args) {
            static_assert(std::is_base_of<Component, T>(), "Can't add component: type is not derived from Component.");

            std::type_index ti = std::type_index(typeid(T));
            if(m_Components.find(ti) != m_Components.end()) {
                Logger::Error("Can't add component: type already exists.");
                return nullptr;
            }

            Component *c = new T(this, args...);
            m_Components.emplace(ti, c);

            return (T *) c;
        }

        template<typename T>
        T *GetComponent() {
            static_assert(std::is_base_of<Component, T>(), "Can't get component: type is not derived from Component.");

            auto iter = m_Components.find(std::type_index(typeid(T)));
            if(iter != m_Components.end()) {
                return (T *) iter->second;
            }
            return nullptr;
        }

        template<typename T>
        void DestroyComponent() {
            std::type_index ti = std::type_index(typeid(T));
            if(GetComponent<T>() != nullptr) {
                m_Components.erase(ti);
            }
        }
    };
};
