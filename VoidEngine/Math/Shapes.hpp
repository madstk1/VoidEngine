#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Linear.hpp>

namespace VOID_NS {
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

    struct MVP {
        Matrix4 model = Matrix4(0.0f);
        Matrix4 view  = Matrix4(0.0f);
        Matrix4 proj  = Matrix4(0.0f);
    };
};
