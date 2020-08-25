#ifndef VOID_ECS_MESH_COMPONENT_H__
#define VOID_ECS_MESH_COMPONENT_H__

#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class MeshComponent : Component {
    public:
        MeshComponent() : Component(true) {}

        std::vector<Vertex>  vertices;
        std::vector<u32>     indices;
        std::vector<Vector3> normals;
    };
};

#endif /* VOID_ECS_MESH_COMPONENT_H__ */
