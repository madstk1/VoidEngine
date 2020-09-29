#pragma once

#include <VoidEngine/Math/Vector2.hpp>
#include <VoidEngine/Math/Vector3.hpp>
#include <VoidEngine/Math/Vector4.hpp>

#include <VoidEngine/Math/Matrix2.hpp>
#include <VoidEngine/Math/Matrix3.hpp>
#include <VoidEngine/Math/Matrix4.hpp>

namespace VOID_NS {
    /**
     *  Vectors
     */

    typedef vec2<f32> Vector2;
    typedef vec2<f32> Vector2f;
    typedef vec2<f64> Vector2d;
    typedef vec2<i32> Vector2i;
    typedef vec2<u64> Vector2u;

    typedef vec3<f32> Vector3;
    typedef vec3<f32> Vector3f;
    typedef vec3<f64> Vector3d;
    typedef vec3<i32> Vector3i;
    typedef vec3<u64> Vector3u;

    typedef vec4<f32> Vector4;
    typedef vec4<f32> Vector4f;
    typedef vec4<f64> Vector4d;
    typedef vec4<i32> Vector4i;
    typedef vec4<u64> Vector4u;

    /**
     *  Matrices
     */

    typedef mat2<f32> Matrix2;
    typedef mat2<f32> Matrix2f;
    typedef mat2<f64> Matrix2d;
    typedef mat2<i32> Matrix2i;
    typedef mat2<u32> Matrix2u;

    typedef mat3<f32> Matrix3;
    typedef mat3<f32> Matrix3f;
    typedef mat3<f64> Matrix3d;
    typedef mat3<i32> Matrix3i;
    typedef mat3<u32> Matrix3u;

    typedef mat4<f32> Matrix4;
    typedef mat4<f32> Matrix4f;
    typedef mat4<f64> Matrix4d;
    typedef mat4<i32> Matrix4i;
    typedef mat4<u32> Matrix4u;
    
    
    /**
     *  Quaternions
     */
    
    typedef glm::qua<f32> Quaternion;
    typedef glm::qua<f64> Quaterniond;
    typedef glm::qua<i32> Quaternioni;
    typedef glm::qua<u32> Quaternionu;
};
