#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    World::World(const ApplicationInfo &info) {
    }

    World::~World() {
    }

    void World::AddGameObject(Entity *entity) {
        VOID_ASSERT(entity != nullptr, "Trying to add NULL entity to game-world.");

        m_WorldObjects.Append(entity);
    }
    
    void World::DestroyGameObject(Entity *entity) {
        VOID_ASSERT(entity != nullptr, "Trying to destroy NULL entity from game-world.");

        m_WorldObjects.Remove(entity);
    }

    void World::Start() {
        for(Entity *e : m_WorldObjects) {
            e->Start();
        }
    }

    void World::Update() {
        for(Entity *e : m_WorldObjects) {
            e->Update();
        }
    }

    void World::FixedUpdate() {
        for(Entity *e : m_WorldObjects) {
            e->FixedUpdate();
        }
    }
};
