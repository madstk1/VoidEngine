#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/ECS/Entity.hpp>

namespace VOID_NS {
    Entity::Entity() {
        g_World->AddGameObject(this);
    }

    Entity::Entity(std::string entityName) : Entity() {
        this->name = entityName;
    }

    Entity::~Entity() {
        g_World->DestroyGameObject(this);
    }
};
