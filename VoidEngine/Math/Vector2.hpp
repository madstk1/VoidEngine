#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <glm/glm.hpp>

namespace VOID_NS {
    template<typename T>
    class vec2 : public glm::vec<2, T> {
    private:
        const f32 length() const = delete;
            
    public:
        typedef vec2<T>        self;
        typedef glm::vec<2, T> base;

        vec2()                   : base() {}
        vec2(base v)             : base(v) {}
        vec2(const self &v)      : base(v) {}
        vec2(f32 x)              : base(x, x) {}
        vec2(f32 x, f32 y)       : base(x, y) {}

        const f32        Length()                 const { return glm::length((base) *this); }
        const self       Normalized()             const { return glm::normalize(*this); }
        const f32        Distance(self v)         const { return glm::length(*this - v); }
        const f32        Dot(self v)              const { return glm::dot((base) *this, v); }

        void             Normalize()              { *this = Normalized(); }

        static f32       Length(self d)           { return d.Length(); }
        static self      Normalize(self d)        { return d.Normalized(); }
        static f32       Distance(self a, self b) { return a.Distance(b); }
        static f32       Dot(self a, self b)      { return a.Dot(b); }

        static self      Zero()  { return {0}; }
        static self      One()   { return {1}; }
        static self      Right() { return { 1,  0}; }
        static self      Left()  { return {-1,  0}; }
        static self      Up()    { return { 0,  1}; }
        static self      Down()  { return { 0, -1}; }
    };

    typedef vec2<f32> Vector2;
    typedef vec2<f32> Vector2f;
    typedef vec2<f64> Vector2d;
    typedef vec2<i32> Vector2i;
    typedef vec2<u64> Vector2u;
};
