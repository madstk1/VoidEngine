#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/ECS/Entity.hpp>

namespace VOID_NS {
    Entity::Entity() {
        World::Get()->AddEntity(this);
    }

    Entity::Entity(string name) : Entity() {
        this->name = name;
    }

    Entity::~Entity() {
        World::Get()->RemoveEntity(this);
    }
};
