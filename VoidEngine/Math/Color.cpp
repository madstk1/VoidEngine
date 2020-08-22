#include <VoidEngine/Math/Color.hpp>

namespace VOID_NS {
    Color::Color() : Vector4(0.f, 0.f, 0.f, 1.f) {}

    Color::Color(f32 x) : Vector4(x, x, x, 1.f) {}
    Color::Color(f32 r, f32 g, f32 b) : Vector4(r, g, b, 1.f) {}
    Color::Color(f32 r, f32 g, f32 b, f32 a) : Vector4(r, g, b, a) {}

    Color::Color(const Color &c) {
        *this = c;
    }

    Color::Color(const Vector4 &c) {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }
    
    Color Color::Grayscale() {
        return Color(
            r * 0.2126f,
            g * 0.7152f,
            b * 0.0722f
        );
    }

    void Color::operator = (const Color &c) {
        this->r = c.r;
        this->g = c.g;
        this->b = c.b;
        this->a = c.a;
    }
};
