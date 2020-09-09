#ifndef VOID_ECS_ENTITIES_CAMERA_H__
#define VOID_ECS_ENTITIES_CAMERA_H__

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/ECS/Entity.hpp>

namespace VOID_NS {
    class Camera : public Entity {
    public:
        f32 fieldOfView = 80.0f;
        f32 zNear = 0.1f;
        f32 zFar  = 100.0f;

        Camera() : Entity("Camera") {
            if(g_Camera == nullptr) {
                g_Camera = this;
            }

            position = Vector3(0.0f, 0.0f, 2.5f);
            rotation = Vector3(0.0f, 0.0f, -90.0f);
        }

        Vector3 Up() {
            return Vector3(0, 1, 0);
        }

        Vector3 Forward() {
            Vector3 dir = {
                cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y)), /* X */
                sin(glm::radians(rotation.y)),                                 /* Y */
                sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y)), /* Z */
            };
            return glm::normalize(dir);
        }

        Vector3 Right() {
            return glm::normalize(glm::cross(Forward(), Up()));
        }
    };
};

#endif /* VOID_ECS_ENTITIES_CAMERA_H__ */
