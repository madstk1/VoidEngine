#ifndef VOID_ECS_ENTITIES_QUAD_H__
#define VOID_ECS_ENTITIES_QUAD_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/Math/Color.hpp>

namespace VOID_NS {
    class Quad : public Entity {
    public:
        Quad() : Entity("Quad") {
            this->renderable = true;
            MeshComponent *mc = AddComponent(new MeshComponent());
            Mesh *mesh = mc->mesh = new Mesh();

            mesh->vertices.push_back(Vertex(Vector3(-1.0f, 0.0f, -1.0f), Color::White()));
            mesh->vertices.push_back(Vertex(Vector3(-1.0f, 0.0f,  1.0f), Color::White()));
            mesh->vertices.push_back(Vertex(Vector3( 1.0f, 0.0f,  1.0f), Color::White()));
            mesh->vertices.push_back(Vertex(Vector3( 1.0f, 0.0f, -1.0f), Color::White()));

            mesh->indices.insert(mesh->indices.begin(), {
                2, 1, 0,
                0, 3, 2
            });
        }
        
    protected:
    private:
    };
};

#endif /* VOID_ECS_ENTITIES_QUAD_H__ */
