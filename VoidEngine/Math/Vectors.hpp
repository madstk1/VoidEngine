#ifndef VOID_MATH_VECTORS_H__
#define VOID_MATH_VECTORS_H__

#include <VoidEngine/Core/Common.hpp>

/**
 *  Vectors
 */

typedef glm::vec<2, f32> Vector2;
typedef glm::vec<2, f64> Vector2d;
typedef glm::vec<2, i32> Vector2i;
typedef glm::vec<2, u32> Vector2u;

typedef glm::vec<3, f32> Vector3;
typedef glm::vec<3, f64> Vector3d;
typedef glm::vec<3, i32> Vector3i;
typedef glm::vec<3, u32> Vector3u;

typedef glm::vec<4, f32> Vector4;
typedef glm::vec<4, f64> Vector4d;
typedef glm::vec<4, i32> Vector4i;
typedef glm::vec<4, u32> Vector4u;

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
