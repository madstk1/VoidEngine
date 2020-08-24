#ifndef VOID_CORE_COMMON_H__
#define VOID_CORE_COMMON_H__

#include <cstddef>
#include <cstdint>
#include <glm/glm.hpp>

#include <VoidEngine/Core/Errors.hpp>

#define VOID_NS     Void

#define LEN(x)      (sizeof(x)/sizeof(x[0]))
#define MAX(a,b)    (a > b ? a : b)
#define MIN(a,b)    (a < b ? a : b)

typedef uint64_t    u64;
typedef  int64_t    i64;

typedef uint32_t    u32;
typedef  int32_t    i32;

typedef uint16_t    u16;
typedef  int16_t    i16;

typedef uint8_t     u8;
typedef  int8_t     i8;

typedef double      f64;
typedef float       f32;

typedef __u_char    uchar;

/**
 * __bool_true_false_are_defined is
 * defined in stdbool.h/cstdbool, when bool is
 * already defined
 */
#if ! defined(__cplusplus) && ! defined(__bool_true_false_are_defined)
typedef uchar       bool;
#define false       0
#define true        1
#endif /* __cplusplus && __bool_true_false_are_defined */

#endif /* VOID_CORE_COMMON_H__ */
