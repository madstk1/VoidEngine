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
            MeshComponent *mc = AddComponent<MeshComponent>();
            Mesh *mesh = mc->mesh = new Mesh();

            mesh->vertices.Append(Vertex(Vector3(-1.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f)));
            mesh->vertices.Append(Vertex(Vector3(-1.0f, 0.0f,  1.0f), Vector3(0.0f, 1.0f, 0.0f)));
            mesh->vertices.Append(Vertex(Vector3( 1.0f, 0.0f,  1.0f), Vector3(0.0f, 1.0f, 0.0f)));
            mesh->vertices.Append(Vertex(Vector3( 1.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f)));

            mesh->indices.Append({
                0, 1, 2,
                2, 3, 0
            });
        }
        
    protected:
    private:
    };
};

#endif /* VOID_ECS_ENTITIES_QUAD_H__ */
