#pragma once

#include <map>
#include <typeindex>
#include <type_traits>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Vectors.hpp>

namespace VOID_NS {
    template<class T>
    constexpr bool IsComponent() {
        return std::is_base_of<Component, T>::value;
    }

    class Entity {
    protected:
        std::map<std::type_index, Component *> m_Components;

    public:
        string name = "Void Entity";
        bool enabled = true;

        Vector3 position = Vector3(0, 0, 0);
        Vector3 rotation = Vector3(0, 0, 0);
        Vector3 scale    = Vector3(1, 1, 1);

        Entity();
        Entity(string);
        ~Entity();

        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}

        Vector3 Up();
        Vector3 Forward();
        Vector3 Right();

        void LookAt(Vector3);

        template<class T>
        T *AddComponent() {
            if(!IsComponent<T>()) {
                Logger::Error("Can't add component '", Logger::GetClassName<T>(), "', since it's not derived from Component.");
                return nullptr;
            }

            if(GetComponent<T>() != nullptr) {
                Logger::Error("Can't add component '", Logger::GetClassName<T>(), "', since it already exists on this entity.");
                return nullptr;
            }

            std::type_index tindex = std::type_index(typeid(T));
            Component *c = new T();
            c->m_Entity = this;
            
            this->m_Components.emplace(tindex, c);
            return (T *) c;
        }

        template<class T>
        T *GetComponent() {
            if(!IsComponent<T>()) {
                Logger::Error("Can't get component '", Logger::GetClassName<T>(), "', since it's not derived from Component.");
                return nullptr;
            }

            std::type_index tindex = std::type_index(typeid(T));
            for(auto c : this->m_Components) {
                if(tindex == c.first) {
                    return (T *) c.second;
                }
            }
            return nullptr;
        }

        template<class T>
        void DestroyComponent() {
            if(!IsComponent<T>()) {
                Logger::Error("Can't get component '", Logger::GetClassName<T>(), "', since it's not derived from Component.");
                return;
            }

            std::type_index tindex = std::type_index(typeid(T));
            for(auto c : this->m_Components) {
                if(tindex == c.first) {
                    this->m_Components.erase(tindex);
                }
            }
        }
    };
};
