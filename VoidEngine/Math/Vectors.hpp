#ifndef VOID_MATH_VECTORS_H__
#define VOID_MATH_VECTORS_H__

#include <VoidEngine/Core/Common.hpp>

/**
 *  Vectors
 */

#include <VoidEngine/Math/Vector2.hpp>
#include <VoidEngine/Math/Vector3.hpp>
#include <VoidEngine/Math/Vector4.hpp>

/**
 *  Matrices
 */

typedef glm::mat<2, 2, f32> Mat2;
typedef glm::mat<2, 2, f64> Mat2d;
typedef glm::mat<2, 2, i32> Mat2i;
typedef glm::mat<2, 2, u32> Mat2u;

typedef glm::mat<3, 3, f32> Mat3;
typedef glm::mat<3, 3, f64> Mat3d;
typedef glm::mat<3, 3, i32> Mat3i;
typedef glm::mat<3, 3, u32> Mat3u;

typedef glm::mat<4, 4, f32> Mat4;
typedef glm::mat<4, 4, f64> Mat4d;
typedef glm::mat<4, 4, i32> Mat4i;
typedef glm::mat<4, 4, u32> Mat4u;

/**
 *  Quaternions
 */

typedef glm::qua<f32> Quaternion;
typedef glm::qua<f64> Quaterniond;
typedef glm::qua<i32> Quaternioni;
typedef glm::qua<u32> Quaternionu;

#endif /* VOID_MATH_VECTORS_H__ */
