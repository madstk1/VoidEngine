#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/ECS/Entity.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace VOID_NS {
    Entity::Entity() {
        g_World->AddGameObject(this);
    }

    Entity::Entity(std::string entityName) : Entity() {
        this->name = entityName;
    }

    Entity::~Entity() {
        g_World->DestroyGameObject(this);
    }

    void Entity::LookAt(Vector3 target) {
        Quaternion fin;
        Vector3    eur;

        Vector3 up  = {0, 1, 0};
        Vector3 dir = glm::normalize(target - position);

        do {
            if(glm::length(glm::cross(dir, up)) == 0.0f) {
                fin = Quaternion(1, 0, 0, 0);
                break;
            }

            if(dir.z >= 0.0f) {
                fin = glm::quatLookAtLH(dir, up);
            } else {
                fin = glm::quatLookAtLH(-dir, up);
            }
        } while(false);

        eur = glm::eulerAngles(fin);
        eur = glm::degrees((glm::vec3) eur);

        if(dir.z >= 0.0f) {
            rotation.x = -eur.y + 90;
            rotation.y = -eur.x;
        } else {
            rotation.x = -eur.y + 270;
            rotation.y =  eur.x;
        }
    }

    Vector3 Entity::Up() {
        return Vector3(0, 1, 0);
    }
    
    Vector3 Entity::Forward() {
        Vector3 dir = {
            static_cast<f32>(cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y))), /* X */
            static_cast<f32>(sin(glm::radians(rotation.y))),                                 /* Y */
            static_cast<f32>(sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y))), /* Z */
        };
        return glm::normalize(dir);
    }
    
    Vector3 Entity::Right() {
        return Vector3::Normalize(Vector3::Cross(Forward(), Up()));
    }
};
