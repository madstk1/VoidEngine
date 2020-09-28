#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Transform.hpp>

namespace VOID_NS {
    class Entity;

    class Component {
    protected:
        Entity *m_Parent = nullptr;

        Component(Entity *parent) : m_Parent(parent) {}

    public:
        virtual ~Component() = default;

        inline const Entity *Parent() const {
            return m_Parent;
        }
    };
};
