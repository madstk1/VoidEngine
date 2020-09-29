#pragma once

#include <map>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Transform.hpp>

namespace VOID_NS {
    /**
     *  Entity / world object class.
     *
     *  Entities can hold components, which are
     *  used to transform the alter the entity.
     *
     *  Each entity has a transform, but isn't necessarily rendered.
     */
    class Entity {
    protected:
        std::map<std::type_index, Component *> m_Components;

    public:
        /**
         *  The entity's name.
         *  Mostly used for logging and differentiating multiple entities.
         */
        string name = "Void Entity";

        /**
         *  If not enabled, the entity will not be rendered,
         *  nor trigger any delegates.
         */
        bool enabled = true;

        /**
         *  The entity's transform.
         *  This includes position, rotation and scale.
         */
        Transform transform;

        /**
         *  Create entity with default name.
         */
        Entity();

        /**
         *  Create entity with supplied name.
         */
        Entity(string);

        ~Entity();

        /**
         *  This method is run on Entity creation.
         */
        virtual void Start() {}

        /**
         *  This method is run every frame.
         */
        virtual void Update() {}

        /**
         *  Runs every (1.0 / FixedUpdateInterval) seconds.
         *  See Engine-class.
         */
        virtual void FixedUpdate() {}

        /**
         *  Add component to the entity.
         *  Only one of each component can exist on the entity.
         *
         *  NOTE: The passed class MUST be derived from Component.
         */
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

        /**
         *  Retrieve component from the entity or nullptr if it doesn't exist.
         *
         *  NOTE: The passed class MUST be derived from Component.
         */
        template<typename T>
        T *GetComponent() {
            static_assert(std::is_base_of<Component, T>(), "Can't get component: type is not derived from Component.");

            auto iter = m_Components.find(std::type_index(typeid(T)));
            if(iter != m_Components.end()) {
                return (T *) iter->second;
            }
            return nullptr;
        }

        /**
         *  Destroy component from the Entity.
         *
         *  NOTE: The passed class MUST be derived from Component.
         */
        template<typename T>
        void DestroyComponent() {
            static_assert(std::is_base_of<Component, T>(), "Can't destroy component: type is not derived from Component.");

            std::type_index ti = std::type_index(typeid(T));
            if(GetComponent<T>() != nullptr) {
                m_Components.erase(ti);
            }
        }
    };
};
