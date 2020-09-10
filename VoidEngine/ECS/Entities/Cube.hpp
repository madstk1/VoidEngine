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
        const Vector3 m_Normals[6] = {
            Vector3( 0.000000,  0.000000, -1.000000),
            Vector3( 0.000000,  0.000000,  1.000000),
            Vector3( 1.000000,  0.000000,  0.000000),
            Vector3( 0.000000, -1.000000,  0.000000),
            Vector3(-1.000000,  0.000000,  0.000000),
            Vector3( 0.000000,  1.000000,  0.000000),
        };

    protected:
    public:
        Cube() : Entity() {
            this->name = "Cube"; 
            this->renderable = true;
            MeshComponent *mc = AddComponent<MeshComponent>();
            Mesh *mesh = mc->mesh = new Mesh();

            mesh->vertices.push_back(Vector3( 1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000, -1.000000, -1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000, -1.000000));
            mesh->vertices.push_back(Vector3(-1.000000,  1.000000,  1.000000));
            mesh->vertices.push_back(Vector3( 1.000000,  1.000000,  1.000000));

            for(u32 i = 0; i < 36; i++) {
                mesh->indices.push_back(i);
            }

            u32 i = 0;
            for(Vector3 n : m_Normals) {
                mesh->vertices[i + 0].normal = n;;
                mesh->vertices[i + 1].normal = n;;
                mesh->vertices[i + 2].normal = n;;
                mesh->vertices[i + 3].normal = n;;
                mesh->vertices[i + 4].normal = n;;
                mesh->vertices[i + 5].normal = n;;
                i += 6;
            }
        }
    };
};

#endif /* VOID_ECS_ENTITIES_CUBE_H__ */
