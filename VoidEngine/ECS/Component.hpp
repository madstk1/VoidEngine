#pragma once

#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    class Entity;

    class Component {
    protected:
        Entity *m_Entity;

        Component() {}

    public:
        virtual ~Component() = default;

        Entity *GameObject() { return m_Entity; }

        friend Entity;
    };
};
