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

        void AddEntity(Entity *e) {
            OnEntityCreation(e);
            m_WorldObjects.Append(e);
        }

        void RemoveEntity(Entity *e) {
            OnEntityDestruction(e);
            m_WorldObjects.Remove(e);
        }

    public:
        Delegate<Entity *> OnEntityCreation;
        Delegate<Entity *> OnEntityDestruction;

        void Start() {
            for(Entity *e : m_WorldObjects) {
                e->Start();
            }
        }

        void Update() {
            for(Entity *e : m_WorldObjects) {
                e->Update();
            }
        }

        void FixedUpdate() {
            for(Entity *e : m_WorldObjects) {
                e->FixedUpdate();
            }
        }

        const Vector<Entity *> GetWorldObjects() const {
            return m_WorldObjects;
        }

        friend Entity;
    };
};
