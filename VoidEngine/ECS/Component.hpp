#ifndef VOID_ECS_COMPONENT_H__
#define VOID_ECS_COMPONENT_H__

#include <VoidEngine/Core/Common.hpp>


namespace VOID_NS {
    class Entity;

    class Component {
    private:
    protected:
        Entity *m_GameObject = nullptr;
        bool m_SingleComponent = true;

        Component(bool single) : m_SingleComponent(single) {}

    public:
        ~Component() {}

        inline Entity *GameObject() { return m_GameObject; }

        friend Entity;
    };
};

#endif /* VOID_ECS_COMPONENT_H__ */
