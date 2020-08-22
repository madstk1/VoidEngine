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
        glm::vec3 position;
        Color color;

        Vertex(glm::vec3 pos) : position(pos), color(Color::White()) {}
        Vertex(glm::vec3 pos, Color col) : position(pos), color(col) {}
    };

    template<size_t N>
    class Shape {
    public:
        Vertex vertices[N];
    };

    class Triangle : Shape<3> {
    private:
    protected:
    public:
    };

    class Quad : Shape<4> {
    private:
    protected:
    public:
    };
};

#endif /* VOID_MATH_SHAPES_H__ */
