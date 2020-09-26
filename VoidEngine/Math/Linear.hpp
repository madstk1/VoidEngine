#pragma once

#include <VoidEngine/Core/Common.hpp>

#include <VoidEngine/Math/Vector2.hpp>
#include <VoidEngine/Math/Vector3.hpp>
#include <VoidEngine/Math/Vector4.hpp>

namespace VOID_NS {
    /**
     *  Matrices
     */
    
    typedef glm::mat<2, 2, f32> Matrix2;
    typedef glm::mat<2, 2, f64> Matrix2d;
    typedef glm::mat<2, 2, i32> Matrix2i;
    typedef glm::mat<2, 2, u32> Matrix2u;
    
    typedef glm::mat<3, 3, f32> Matrix3;
    typedef glm::mat<3, 3, f64> Matrix3d;
    typedef glm::mat<3, 3, i32> Matrix3i;
    typedef glm::mat<3, 3, u32> Matrix3u;
    
    typedef glm::mat<4, 4, f32> Matrix4;
    typedef glm::mat<4, 4, f64> Matrix4d;
    typedef glm::mat<4, 4, i32> Matrix4i;
    typedef glm::mat<4, 4, u32> Matrix4u;
    
    /**
     *  Quaternions
     */
    
    typedef glm::qua<f32> Quaternion;
    typedef glm::qua<f64> Quaterniond;
    typedef glm::qua<i32> Quaternioni;
    typedef glm::qua<u32> Quaternionu;
};
