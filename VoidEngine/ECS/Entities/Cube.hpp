#ifndef VOID_ECS_ENTITIES_CUBE_H__
#define VOID_ECS_ENTITIES_CUBE_H__

#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class Cube : public Entity {
    private:
    protected:
    public:
        Cube() : Entity() {
            this->name = "Cube"; 
            this->renderable = true;
            MeshComponent *mc = AddComponent(new MeshComponent());
            mc->mesh = new Mesh();
            Mesh *mesh = mc->mesh;

            /* Front */
            mesh->vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f), Color::Green())); // 0
            mesh->vertices.push_back(Vertex(glm::vec3(1.0f, 0.0f, 0.0f), Color::Green())); // 1
            mesh->vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, 0.0f), Color::Blue()));  // 2
            mesh->vertices.push_back(Vertex(glm::vec3(0.0f, 1.0f, 0.0f), Color::Blue()));  // 3

            /* Back */
            mesh->vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 1.0f), Color::Blue()));  // 4
            mesh->vertices.push_back(Vertex(glm::vec3(1.0f, 0.0f, 1.0f), Color::Blue()));  // 5
            mesh->vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, 1.0f), Color::Green())); // 6
            mesh->vertices.push_back(Vertex(glm::vec3(0.0f, 1.0f, 1.0f), Color::Green())); // 7

            mesh->indices.insert(mesh->indices.begin(), {
                /* Front */
                0, 1, 2, 2, 3, 0,

                /* Back */
                6, 5, 4, 4, 7, 6,

                /* Left */
                5, 2, 1, 5, 6, 2,

                /* Right */
                0, 3, 4, 3, 7, 4,

                /* Bottom */
                4, 1, 0, 4, 5, 1,

                /* Top */
                6, 3, 2, 6, 7, 3
            });
        }
    };
};

#endif /* VOID_ECS_ENTITIES_CUBE_H__ */
