#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/World.hpp>

namespace VOID_NS {
    void World::Start() {
        for(auto &e : m_WorldObjects) {
            e->Start();
        }
    }
    
    void World::Update() {
        for(auto &e : m_WorldObjects) {
            e->Update();
        }
    }
    
    void World::FixedUpdate() {
        for(auto &e : m_WorldObjects) {
            e->FixedUpdate();
        }
    }
    
    void World::AddGameObject(Entity *e) {
        VOID_ASSERT(e != nullptr, "Trying to add NULL entity to game-world.");
        m_WorldObjects.Append(e);
    }

    void World::DestroyGameObject(Entity *e) {
        VOID_ASSERT(e != nullptr, "Trying to destroy NULL entity from game-world.");
        m_WorldObjects.Remove(e);
    }
};
