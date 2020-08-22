#ifndef VOID_MATH_COLOR_H__
#define VOID_MATH_COLOR_H__

#include <type_traits>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Math/Vectors.hpp>

namespace VOID_NS {
    class Color : public Vector4 {
    protected:
    public:
        Color();
        Color(f32);
        Color(f32, f32, f32);
        Color(f32, f32, f32, f32);

        Color(const Color &);
        Color(const Vector4 &);

        Color Grayscale();

        static inline Color Black()   { return Color(0, 0, 0); }
        static inline Color Blue()    { return Color(0, 0, 1); }
        static inline Color Clear()   { return Color(0, 0, 0, 0); }
        static inline Color Cyan()    { return Color(0, 1, 1); }
        static inline Color Gray()    { return Color(0.5f, 0.5f, 0.5f); }
        static inline Color Green()   { return Color(0, 1, 0); }
        static inline Color Magenta() { return Color(1, 0, 1); }
        static inline Color Red()     { return Color(1, 0, 0); }
        static inline Color White()   { return Color(1, 1, 1); }
        static inline Color Yellow()  { return Color(1, 1, 0); }

        void operator = (const Color &);
    };
};

#endif /* VOID_MATH_COLOR_H__ */
