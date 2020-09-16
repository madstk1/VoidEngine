#ifndef VOID_ECS_MESH_COMPONENT_H__
#define VOID_ECS_MESH_COMPONENT_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Mesh.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

namespace VOID_NS {
    class MeshComponent : public Component {
    public:
        Mesh *mesh = nullptr;
        Shader *shader = nullptr;

        MeshComponent(Mesh *mesh = nullptr) : Component(true) {
            this->mesh   = mesh;
            this->shader = ShaderLibrary::GetShader("Default");
        }
    };
};

#endif /* VOID_ECS_MESH_COMPONENT_H__ */
