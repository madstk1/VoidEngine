#ifndef VOID_ECS_ENTITIES_FIRSTPERSONCAMERA_H__
#define VOID_ECS_ENTITIES_FIRSTPERSONCAMERA_H__

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Input/InputManager.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/ECS/Entities/Camera.hpp>

namespace VOID_NS {
    class FirstPersonCamera : public Camera {
    public:
        f32 lookSensitivity = 1.0f;

        FirstPersonCamera() : Camera() {
        }

        virtual void Update() override {
            rotation.x += Input::GetAxis("Mouse X") * lookSensitivity;
            rotation.y += Input::GetAxis("Mouse Y") * lookSensitivity;

            if(rotation.y >  89.0f) { rotation.y =  89.0f; }
            if(rotation.y < -89.0f) { rotation.y = -89.0f; }
        }
    };
};

#endif /* VOID_ECS_ENTITIES_FIRSTPERSONCAMERA_H__ */
