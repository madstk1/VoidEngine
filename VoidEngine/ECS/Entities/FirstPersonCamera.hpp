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
        f32 moveSpeed = 5.0f;
        f32 lookSensitivity = 1.0f;

        FirstPersonCamera() : Camera() {
        }

        virtual void Update() override {
            rotation.x += Input::GetAxis("Mouse X") * lookSensitivity;
            rotation.y += Input::GetAxis("Mouse Y") * lookSensitivity;

            if(rotation.y >  89.0f) { rotation.y =  89.0f; }
            if(rotation.y < -89.0f) { rotation.y = -89.0f; }

            if(Input::GetKeyDown(Keycode::KeyW)) {
                position += Forward() * moveSpeed * Time::GetDeltaTime();
            }
    
            if(Input::GetKeyDown(Keycode::KeyS)) {
                position -= Forward() * moveSpeed * Time::GetDeltaTime();
            }
    
            if(Input::GetKeyDown(Keycode::KeyD)) {
                position += Right() * moveSpeed * Time::GetDeltaTime();
            }
    
            if(Input::GetKeyDown(Keycode::KeyA)) {
                position -= Right() * moveSpeed * Time::GetDeltaTime();
            }
    
            if(Input::GetKeyDown(Keycode::KeySpace)) {
                position += Vector3(0, 1, 0) * moveSpeed * Time::GetDeltaTime();
            }
    
            if(Input::GetKeyDown(Keycode::KeyC)) {
                position -= Vector3(0, 1, 0) * moveSpeed * Time::GetDeltaTime();
            }
        }
    };
};

#endif /* VOID_ECS_ENTITIES_FIRSTPERSONCAMERA_H__ */
