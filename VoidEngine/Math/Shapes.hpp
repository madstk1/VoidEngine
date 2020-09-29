#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Linear.hpp>

namespace VOID_NS {
    /**
     *  Vertex class.
     *  This is used primarily for meshes and rendering.
     */
    class Vertex {
    public:
        Vector3 position;
        Vector3 normal;
        Vector2 texCoords;

        Vector3 tangents;
        Vector3 bitangents;

        Vertex() {}

        Vertex(Vector3 pos)
            : position(pos) {}

        Vertex(Vector3 pos, Vector3 normal)
            : position(pos),
              normal(normal) {}

        Vertex(Vector3 pos, Vector3 normal, Vector2 texCoords)
            : position(pos),
              normal(normal),
              texCoords(texCoords) {}
    };

    /**
     *  MVP class.
     *  Short for Model-View-Projection, this is used for matrix manipulation.
     */
    struct MVP {
        Matrix4 model = Matrix4();
        Matrix4 view  = Matrix4();
        Matrix4 proj  = Matrix4();
    };
};
