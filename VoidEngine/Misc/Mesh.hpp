#ifndef VOID_MISC_MESH_H__
#define VOID_MISC_MESH_H__

#include <vector>

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class Mesh {
    public:
        std::vector<Vertex>  vertices;
        std::vector<u32>     indices;
        std::vector<Vector3> normals;

        Mesh() {}

        Mesh(
            std::vector<Vertex> vertices
        ) : vertices(vertices) {}

        Mesh(
            std::vector<Vertex> vertices,
            std::vector<u32> indices
        ) : vertices(vertices), indices(indices) {}

        Mesh(
            std::vector<Vertex> vertices,
            std::vector<u32> indices,
            std::vector<Vector3> normals
        ) : vertices(vertices), indices(indices), normals(normals) {}

        virtual ~Mesh() = default;

    protected:
    private:
    };
};

#endif /* VOID_MISC_MESH_H__ */
