#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Linear.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class Entity;

    /**
     *  Transform class of Void.
     *  This contains world information of an entity.
     */
    class Transform {
    public:
        /**
         *  Position of the entity, in world-space.
         */
        Vector3f position;

        /**
         *  Rotation of the entity, in world-space.
         */
        Vector3f rotation;

        /**
         *  Scale of the entity, in world-space.
         */
        Vector3f scale;

        /**
         *  Constructor for Transform.
         *  By default, everything but scale is zero'd out.
         */
        Transform(Vector3f position = {}, Vector3f rotation = {}, Vector3f scale = Vector3f(1.0f)) {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        virtual ~Transform() = default;

        /**
         *  Transfer transform information.
         */
        Transform &operator = (const Transform &t) {
            this->position = t.position;
            this->rotation = t.rotation;
            this->scale = t.scale;

            return *this;
        }

        /**
         *  Compare operator.
         */
        bool operator == (const Transform &v) const {
            return (position == v.position) &&
                   (rotation == v.rotation) &&
                   (scale    == v.scale);
        }

        /**
         *  Compare operator.
         */
        bool operator != (const Transform &v) const {
            return !(*this == v);
        }

        /**
         *  Returns the transform Up-vector.
         *  Currently, returns the world-space up vector.
         */
        const Vector3f Up() const {
            return {0, 1, 0};
        }

        /**
         *  Returns the transform Forward-vector, based on the rotation of the entity.
         */
        const Vector3f Forward() const {
            return Vector3f(
                cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y)), /* X */
                sin(glm::radians(rotation.y)),                                 /* Y */
                sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y))  /* Z */
            ).Normalized();
        }

        /**
         *  Returns the transform Right-vector, based on the rotation of the entity.
         */
        const Vector3 Right() const {
            return glm::normalize(glm::cross(Forward(), Up()));
        }

        /**
         *  Rotates the object to look at the target position.
         */
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
