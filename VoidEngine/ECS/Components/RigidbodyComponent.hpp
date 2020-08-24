#ifndef VOID_ECS_RIGIDBODY_COMPONENT_H__
#define VOID_ECS_RIGIDBODY_COMPONENT_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>

namespace VOID_NS {
    class RigidbodyComponent : Component {
    private:
    protected:
    public:
        RigidbodyComponent() : Component(true) {}

        float mass = 1.0f;
        float gravity = -9.81f;
        bool  useGravity = true;
    };
};

#endif /* VOID_ECS_RIGIDBODY_COMPONENT_H__ */
