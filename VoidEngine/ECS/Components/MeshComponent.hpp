#ifndef VOID_ECS_MESH_COMPONENT_H__
#define VOID_ECS_MESH_COMPONENT_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Material.hpp>
#include <VoidEngine/Misc/Mesh.hpp>

namespace VOID_NS {
    class MeshComponent : public Component {
    public:
        Mesh *mesh = nullptr;
        Material *material = Material::GetDefault();

        MeshComponent(Mesh *mesh = nullptr) : Component(true) {
            this->mesh = mesh;
        }
    };
};

#endif /* VOID_ECS_MESH_COMPONENT_H__ */
