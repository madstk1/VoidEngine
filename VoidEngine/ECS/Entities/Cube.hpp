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

            /* Front */
            mc->vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f), Color::Green())); // 0
            mc->vertices.push_back(Vertex(glm::vec3(1.0f, 0.0f, 0.0f), Color::Green())); // 1
            mc->vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, 0.0f), Color::Blue()));  // 2
            mc->vertices.push_back(Vertex(glm::vec3(0.0f, 1.0f, 0.0f), Color::Blue()));  // 3

            /* Back */
            mc->vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 1.0f), Color::Blue()));  // 4
            mc->vertices.push_back(Vertex(glm::vec3(1.0f, 0.0f, 1.0f), Color::Blue()));  // 5
            mc->vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, 1.0f), Color::Green())); // 6
            mc->vertices.push_back(Vertex(glm::vec3(0.0f, 1.0f, 1.0f), Color::Green())); // 7

            mc->indices.insert(mc->indices.begin(), {
                /* Front */
                2, 1, 0, 0, 3, 2,

                /* Back */
                4, 5, 6, 6, 7, 4,

                /* Left */
                1, 2, 5, 2, 6, 5,

                /* Right */
                4, 3, 0, 4, 7, 3,

                /* Bottom */
                0, 1, 4, 1, 5, 4,

                /* Top */
                2, 3, 6, 3, 7, 6
            });
        }
    };
};

#endif /* VOID_ECS_ENTITIES_CUBE_H__ */
