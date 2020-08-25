#ifndef VOID_ECS_CAMERA_COMPONENT_H__
#define VOID_ECS_CAMERA_COMPONENT_H__

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>

namespace VOID_NS {
    class CameraComponent : public Component {
    public:
        f32 fieldOfView = 80.0f;
        f32 zNear = 0.1f;
        f32 zFar  = 100.0f;

        CameraComponent() : Component(true) {
            if(g_Camera == nullptr) {
                g_Camera = this;
            }
        }

        Vector3 Up() {
            return Vector3(0, 1, 0);
        }

        Vector3 Forward() {
            return glm::normalize(Vector3(
                cos(glm::radians(GameObject()->rotation.x)) * cos(glm::radians(GameObject()->rotation.y)),
                sin(glm::radians(GameObject()->rotation.y)),
                sin(glm::radians(GameObject()->rotation.x)) * cos(glm::radians(GameObject()->rotation.y))
            ));
        }

        Vector3 Right() {
            return glm::normalize(glm::cross(Forward(), Up()));
        }

    protected:
    private:
    };
};

#endif /* VOID_ECS_CAMERA_COMPONENT_H__ */
