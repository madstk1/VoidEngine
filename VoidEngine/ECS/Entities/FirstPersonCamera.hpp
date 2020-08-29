#ifndef VOID_ECS_ENTITIES_FIRSTPERSONCAMERA_H__
#define VOID_ECS_ENTITIES_FIRSTPERSONCAMERA_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/ECS/Components/CameraComponent.hpp>

namespace VOID_NS {
    class FirstPersonCamera : public Entity {
    public:
        FirstPersonCamera() : Entity("First Person Camera") {
            this->renderable = false;
            AddComponent(new CameraComponent());
        }
    };
};

#endif /* VOID_ECS_ENTITIES_FIRSTPERSONCAMERA_H__ */
