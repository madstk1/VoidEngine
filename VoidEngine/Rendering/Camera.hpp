#ifndef VOID_RENDERING_CAMERA_H__
#define VOID_RENDERING_CAMERA_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Vectors.hpp>

namespace VOID_NS {
    class Camera {
    public:
        Vector3 position = Vector3(0.0f, 0.0f, 2.5f);
        Vector3 rotation = Vector3(0.0f, 0.0f, -90.0f);
        f32 fieldOfView = 80.0f;

        Camera() {
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

#endif /* VOID_RENDERING_CAMERA_H__ */
