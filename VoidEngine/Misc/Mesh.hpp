#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class Mesh {
    public:
        Vector<Vertex> vertices;
        Vector<Index>  indices;

        Mesh() {}

        Mesh(
            Vector<Vertex> vertices
        ) : vertices(vertices) {}

        Mesh(
            Vector<Vertex> vertices,
            Vector<Index> indices
        ) : vertices(vertices), indices(indices) {}

        virtual ~Mesh() = default;
    };
};
