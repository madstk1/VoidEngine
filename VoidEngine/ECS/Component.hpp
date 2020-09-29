#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Transform.hpp>

namespace VOID_NS {
    class Entity;

    /**
     *  Entity abstract-component.
     *
     *  This is used to define the use of entities.
     *  For default components, see VoidEngine/ECS/Components
     */
    class Component {
    protected:
        /**
         *  Parent entity.
         *  NOTE: If parent is nullptr, the component is invalid.
         */
        Entity *m_Parent = nullptr;

        /**
         *  Create component with the passed entity as parent.
         *  NOTE: Must include parent entity and it cannot be null.
         */
        Component(Entity *parent) : m_Parent(parent) {
            Logger::Assert(parent != nullptr, "Passed parent is null.");
        }

    public:
        virtual ~Component() = default;

        /**
         *  Retuns the parent of the component.
         */
        inline const Entity *Parent() const {
            return m_Parent;
        }
    };
};
