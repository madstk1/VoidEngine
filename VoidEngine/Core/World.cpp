#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    World::World() {
    }

    World::~World() {
    }

    void World::AddGameObject(Entity *entity) {
        VOID_ASSERT(entity != nullptr, "Trying to add NULL entity to game-world.");

        m_WorldObjects.push_back(entity);
        OnEntityCreate(entity);
    }
    
    void World::DestroyGameObject(Entity *entity) {
        VOID_ASSERT(entity != nullptr, "Trying to destroy NULL entity from game-world.");

        u32 i = 0;
        for(const Entity *e : m_WorldObjects) {
            if(e == entity) {
                m_WorldObjects.erase(m_WorldObjects.begin() + i);
                return;
            }
            i++;
        }
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
