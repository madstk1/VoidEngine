#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Misc/Singleton.hpp>

namespace VOID_NS {
    class World : public Singleton<World> {
    protected:
        Vector<Entity *> m_WorldObjects;

    public:
        World() {}
        virtual ~World() = default;

        void Start();
        void Update();
        void FixedUpdate();

        void AddGameObject(Entity *);
        void DestroyGameObject(Entity *);

        inline Vector<Entity *> GetWorldObjects() {
            return m_WorldObjects;
        }
    };
};
