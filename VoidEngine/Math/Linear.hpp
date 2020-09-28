#pragma once

#include <VoidEngine/Core/Common.hpp>

#include <VoidEngine/Math/Vector2.hpp>
#include <VoidEngine/Math/Vector3.hpp>
#include <VoidEngine/Math/Vector4.hpp>

#include <VoidEngine/Math/Matrix2.hpp>
#include <VoidEngine/Math/Matrix3.hpp>
#include <VoidEngine/Math/Matrix4.hpp>

namespace VOID_NS {
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
