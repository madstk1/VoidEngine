#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Math/Linear.hpp>

namespace VOID_NS {
    /**
     *  Color class of Void.
     *
     *  Derived from Vector4, but contains extra methods for usefulness.
     */
    class Color : public Vector4 {
    public:
        /**
         *  Create color with default color of opaque black.
         */
        Color();

        /**
         *  Create color with identical RGB and alpha value of 1.
         */
        Color(f32);

        /**
         *  Create color from RGB-values, with an alpha value of 1.
         */
        Color(f32, f32, f32);

        /**
         *  Create color from RGBA-values.
         */
        Color(f32, f32, f32, f32);

        /**
         *  Create color from existing classes.
         */
        Color(const Color &);
        Color(const Vector4 &);

        /**
         *  Returns the grayscale version of the color.
         */
        Color Grayscale();

        /**
         *  Static methods for standard colors.
         */
        static inline Color Black()   { return Color(0, 0, 0); }
        static inline Color Blue()    { return Color(0, 0, 1); }
        static inline Color Clear()   { return Color(0, 0, 0, 0); }
        static inline Color Cyan()    { return Color(0, 1, 1); }
        static inline Color Gray()    { return Color(0.5f); }
        static inline Color Green()   { return Color(0, 1, 0); }
        static inline Color Magenta() { return Color(1, 0, 1); }
        static inline Color Red()     { return Color(1, 0, 0); }
        static inline Color White()   { return Color(1, 1, 1); }
        static inline Color Yellow()  { return Color(1, 1, 0); }

        /**
         *  Operator- / conversion-methods.
         */
        void operator = (const Color &);
        operator Vector3 () { return {r, g, b}; }
    };
};
