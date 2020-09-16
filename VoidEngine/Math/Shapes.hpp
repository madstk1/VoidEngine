#ifndef VOID_MATH_SHAPES_H__
#define VOID_MATH_SHAPES_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Math/Color.hpp>

#include <glm/glm.hpp>

namespace VOID_NS {
    class Vertex {
    public:
        Vector3 position;
        Color color;
        Vector3 normal;
        Vector2 texCoords;

        Vector3 tangents;
        Vector3 bitangents;

        Vertex(Vector3 pos)
            : position(pos),
              color(Color::White()) {}

        Vertex(Vector3 pos, Color col)
            : position(pos),
              color(col) {}

        Vertex(Vector3 pos, Color col, Vector3 normal)
            : position(pos),
              color(col),
              normal(normal) {}

        Vertex(Vector3 pos, Color col, Vector3 normal, Vector2 texCoords)
            : position(pos),
              color(col),
              normal(normal),
              texCoords(texCoords) {}
    };

    struct MVP {
        Mat4 model = Mat4(0.0f);
        Mat4 view  = Mat4(0.0f);
        Mat4 proj  = Mat4(0.0f);
    };
};

#endif /* VOID_MATH_SHAPES_H__ */
