#ifndef VOID_MISC_MESH_H__
#define VOID_MISC_MESH_H__

#include <vector>

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class Mesh {
    public:
        Vector<Vertex>  vertices;
        Vector<u32>     indices;

        Mesh() {}

        Mesh(
            Vector<Vertex> vertices
        ) : vertices(vertices) {}

        Mesh(
            Vector<Vertex> vertices,
            Vector<u32> indices
        ) : vertices(vertices), indices(indices) {}

        virtual ~Mesh() = default;

    protected:
    private:
    };
};

#endif /* VOID_MISC_MESH_H__ */
