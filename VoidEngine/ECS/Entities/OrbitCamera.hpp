#ifndef VOID_ECS_ENTITIES_ORBITCAMERA_H__
#define VOID_ECS_ENTITIES_ORBITCAMERA_H__

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Input/InputManager.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/ECS/Entities/Camera.hpp>

namespace VOID_NS {
    class OrbitCamera : public Camera {
    protected:
        Vector2 m_Position = {0, 0};

        f32 m_MinY = -4.50f;
        f32 m_MaxY = -1.75f;

    public:
        Vector3 orbitPosition;
        f32 lookSensitivity = 1.0f;
        f32 distance = 10.0f;
        bool invertY = true;

        OrbitCamera(Vector3 orbit = Vector3(0)) : Camera() {
            orbitPosition = orbit;
        }

        virtual void Update() override {
            Vector2 temp = {
                Input::GetAxis("Mouse X") * Time::GetDeltaTime() * lookSensitivity,
                Input::GetAxis("Mouse Y") * Time::GetDeltaTime() * lookSensitivity
            };

            temp.y *= (invertY) ? -1 : 1;

            m_Position.x += temp.x;
            m_Position.y -= temp.y;
            m_Position.y = glm::clamp(m_Position.y, m_MinY, m_MaxY);

            Vector3 newPosition = {
                cos(m_Position.x) * cos(m_Position.y),
                sin(m_Position.y),
                sin(m_Position.x) * cos(m_Position.y)
            };

            newPosition = glm::normalize(newPosition);
            newPosition *= distance;
            newPosition += orbitPosition;

            position = newPosition;

            LookAt(orbitPosition);
        }
    };
};

#endif /* VOID_ECS_ENTITIES_ORBITCAMERA_H__ */
