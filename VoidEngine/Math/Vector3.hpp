#ifndef VOID_MATH_VECTOR3_H__
#define VOID_MATH_VECTOR3_H__

#include <VoidEngine/Core/Common.hpp>
#include <glm/glm.hpp>

namespace VOID_NS {
    template<typename T>
    class vec3 : public glm::vec<3, T> {
    private:
        const f32 length() const = delete;
            
    public:
        typedef vec3<T>        self;
        typedef glm::vec<3, T> base;

        vec3()                    : base() {}
        vec3(base v)              : base(v) {}
        vec3(const self &v)       : base(v) {}
        vec3(f32 x)               : base(x, x) {}
        vec3(f32 x, f32 y)        : base(x, y) {}
        vec3(f32 x, f32 y, f32 z) : base(x, y, z) {}

        const f32        Length()              const { return glm::length((base) *this); }
        const self       Normalized()          const { return glm::normalize(*this); }
        const f32        Distance(self v)      const { return glm::length(*this - v); }
        const f32        Dot(self v)           const { return glm::dot((base) *this, v); }
        const self       Cross(self v)         const { return glm::cross((base) *this, v); }

        void             Normalize()           { *this = Normalized(); }

        static f32       Length(self a)              { return a.Length(); }
        static self      Normalize(self a)           { return a.Normalized(); }
        static f32       Distance(self a, self b)    { return a.Distance(b); }
        static f32       Dot(self a, self b)         { return a.Dot(b); }
        static self      Cross(self a, self b)       { return a.Cross(b); }

        static self      Zero()    { return {0}; }
        static self      One()     { return {1}; }
        static self      Right()   { return { 1,  0,  0}; }
        static self      Left()    { return {-1,  0,  0}; }
        static self      Up()      { return { 0,  1,  0}; }
        static self      Down()    { return { 0, -1,  0}; }
        static self      Forward() { return { 0,  0,  1}; }
        static self      Back()    { return { 0,  0, -1}; }
    };

    typedef vec3<f32> Vector3;
    typedef vec3<f64> Vector3d;
    typedef vec3<i32> Vector3i;
    typedef vec3<u64> Vector3u;
};

#endif /* VOID_MATH_VECTOR3_H__ */
