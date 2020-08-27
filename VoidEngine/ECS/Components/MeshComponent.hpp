#ifndef VOID_ECS_MESH_COMPONENT_H__
#define VOID_ECS_MESH_COMPONENT_H__

#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Mesh.hpp>

namespace VOID_NS {
    class MeshComponent : Component {
    public:
        MeshComponent() : Component(true) {}

        Mesh *mesh = nullptr;
    };
};

#endif /* VOID_ECS_MESH_COMPONENT_H__ */
