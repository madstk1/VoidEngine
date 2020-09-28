#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Linear.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class Entity;

    class Transform {
    public:
        Vector3f position;
        Vector3f rotation;
        Vector3f scale;

        Transform(Vector3f position = {}, Vector3f rotation = {}, Vector3f scale = Vector3f(1.0f)) {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        virtual ~Transform() = default;

        Transform &operator = (const Transform &t) {
            this->position = t.position;
            this->rotation = t.rotation;
            this->scale = t.scale;

            return *this;
        }

        bool operator == (const Transform &v) const {
            return (position == v.position) &&
                   (rotation == v.rotation) &&
                   (scale    == v.scale);
        }

        bool operator != (const Transform &v) const {
            return !(*this == v);
        }

        const Vector3f Up() const {
            return {0, 1, 0};
        }

        const Vector3f Forward() const {
            return Vector3f(
                cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y)), /* X */
                sin(glm::radians(rotation.y)),                                 /* Y */
                sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y))  /* Z */
            ).Normalized();
        }

        const Vector3 Right() const {
            return glm::normalize(glm::cross(Forward(), Up()));
        }

        void LookAt(Vector3f target) {
            Quaternion fin;
            Vector3f up = Up();
            Vector3f dir = glm::normalize(target - position);
    
            do {
                if(glm::length(glm::cross(dir, up)) == 0.0f) {
                    fin = Quaternion(1, 0, 0, 0);
                    break;
                }
    
                if(dir.z >= 0.0f) {
                    fin = glm::quatLookAtLH( dir, up);
                } else {
                    fin = glm::quatLookAtLH(-dir, up);
                }
            } while(false);
    
            Vector3f eur = glm::eulerAngles(fin);
            eur = glm::degrees((glm::vec3) eur);
    
            if(dir.z >= 0.0f) {
                rotation.x = -eur.y + 90;
                rotation.y = -eur.x;
            } else {
                rotation.x = -eur.y + 270;
                rotation.y =  eur.x;
            }
        }
    };
};
