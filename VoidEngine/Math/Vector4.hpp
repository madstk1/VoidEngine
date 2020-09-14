#ifndef VOID_MATH_VECTOR4_H__
#define VOID_MATH_VECTOR4_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Vector2.hpp>
#include <VoidEngine/Math/Vector3.hpp>
#include <glm/glm.hpp>

namespace VOID_NS {
    template<typename T>
    class vec4 : public glm::vec<4, T> {
    private:
        const f32 length() const = delete;
            
    public:
        typedef vec4<T>        self;
        typedef glm::vec<4, T> base;

        vec4()                               : base() {}
        vec4(base v)                         : base(v) {}
        vec4(const self &v)                  : base(v) {}
        vec4(const vec2<T> &v)               : base(v.x, v.y) {}
        vec4(const vec2<T> &v, f32 z, f32 w) : base(v.x, v.y, z, w) {}
        vec4(const vec3<T> &v)               : base(v.x, v.y, v.z) {}
        vec4(const vec3<T> &v, f32 w)        : base(v.x, v.y, v.z, w) {}
        vec4(f32 x)                          : base(x, x, x, x) {}
        vec4(f32 x, f32 y)                   : base(x, y, 0.0f, 0.0f) {}
        vec4(f32 x, f32 y, f32 z)            : base(x, y, z, 0.0f) {}
        vec4(f32 x, f32 y, f32 z, f32 w)     : base(x, y, z, w) {}

        const f32        Length()               const { return glm::length((base) *this); }
        const self       Normalized()           const { return glm::normalize(*this); }
        const f32        Distance(self v)       const { return glm::length(*this - v); }
        const f32        Dot(self v)            const { return glm::dot((base) *this, v); }
        const self       Cross(self v)          const { return glm::cross((base) *this, v); }

        void             Normalize()            { *this = Normalized(); }

        static f32       Length(self a)           { return a.Length(); }
        static self      Normalize(self a)        { return a.Normalized(); }
        static f32       Distance(self a, self b) { return a.Distance(b); }
        static f32       Dot(self a, self b)      { return a.Dot(b); }

        static self      Zero()    { return {0}; }
        static self      One()     { return {1}; }
        static self      Right()   { return { 1,  0,  0, 0}; }
        static self      Left()    { return {-1,  0,  0, 0}; }
        static self      Up()      { return { 0,  1,  0, 0}; }
        static self      Down()    { return { 0, -1,  0, 0}; }
        static self      Forward() { return { 0,  0,  1, 0}; }
        static self      Back()    { return { 0,  0, -1, 0}; }
    };

    typedef vec4<f32> Vector4;
    typedef vec4<f64> Vector4d;
    typedef vec4<i32> Vector4i;
    typedef vec4<u64> Vector4u;
};

#endif /* VOID_MATH_VECTOR4_H__ */
