#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/Misc/Delegate.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Misc/Singleton.hpp>

namespace VOID_NS {
    class World : public Singleton<World> {
    protected:
        Vector<Entity *> m_WorldObjects;

        /**
         *  Add new entity to the world.
         *  This will call OnEntityCreation.
         */
        void AddEntity(Entity *e) {
            OnEntityCreation(e);
            m_WorldObjects.Append(e);
        }

        /**
         *  Remove entity from the world.
         *  This will call OnEntityDestruction.
         */
        void RemoveEntity(Entity *e) {
            OnEntityDestruction(e);
            m_WorldObjects.Remove(e);
        }

        /**
         *  Run Start on all current world objects.
         */
        void Start() {
            for(Entity *e : m_WorldObjects) {
                e->Start();
            }
        }

        /**
         *  Run Update on all current world objects.
         */
        void Update() {
            for(Entity *e : m_WorldObjects) {
                e->Update();
            }
        }

        /**
         *  Run FixedUpdate on all current world objects.
         */
        void FixedUpdate() {
            for(Entity *e : m_WorldObjects) {
                e->FixedUpdate();
            }
        }

    public:
        /**
         *  Runs every time a new entity is created.
         *
         *  NOTE: The passed entity will only be the base entity class.
         *        If the created entity is derived, the base will be passed.
         */
        Delegate<Entity *> OnEntityCreation;

        /**
         *  Runs every time an entity is destroyed.
         */
        Delegate<Entity *> OnEntityDestruction;

        /**
         *  Returns all the current world objects, as entities.
         */
        const Vector<Entity *> GetWorldObjects() const {
            return m_WorldObjects;
        }

        friend Entity;
        friend class Engine;
    };
};
