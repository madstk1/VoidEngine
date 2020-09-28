#ifndef VOID_CORE_COMMON_H__
#define VOID_CORE_COMMON_H__

#include <string>
#include <limits>

#if ! defined(NDEBUG)
#define VOID_ENABLE_DEBUG
#endif

#ifdef VOID_ENABLE_DEBUG
#define VOID_ENABLE_DEBUG_FLAG 1
#else
#define VOID_ENABLE_DEBUG_FLAG 0
#endif

#define VOID_NS     Void

#define LEN(x)      (sizeof(x)/sizeof(x[0]))
#define MAX(a,b)    (a > b ? a : b)
#define MIN(a,b)    (a < b ? a : b)
#define HASBIT(a,b) ((a & b) != 0)

namespace VOID_NS {
    using u64   = uint64_t;
    using u32   = uint32_t;
    using u16   = uint16_t;
    using u8    = uint8_t;
    using i64   = int64_t;
    using i32   = int32_t;
    using i16   = int16_t;
    using i8    = int8_t;
    using f64   = double;
    using f32   = float;
    using uchar = unsigned char;
    using string = std::string;

    using BufferID = u32;
    using ShaderID = u32;
    using FramebufferID = u32;
    using TextureID = u32;
    using CubemapID = u32;
    using Index = u32;

    static const u64 U64_MAX = std::numeric_limits<u64>::max();
    static const u64 U64_MIN = std::numeric_limits<u64>::min();
    static const u32 U32_MAX = std::numeric_limits<u32>::max();
    static const u32 U32_MIN = std::numeric_limits<u32>::min();
    static const u16 U16_MAX = std::numeric_limits<u16>::max();
    static const u16 U16_MIN = std::numeric_limits<u16>::min();
    static const u8  U8_MAX  = std::numeric_limits<u8>::max();
    static const u8  U8_MIN  = std::numeric_limits<u8>::min();

    static const i64 I64_MAX = std::numeric_limits<i64>::max();
    static const i64 I64_MIN = std::numeric_limits<i64>::min();
    static const i32 I32_MAX = std::numeric_limits<i32>::max();
    static const i32 I32_MIN = std::numeric_limits<i32>::min();
    static const i16 I16_MAX = std::numeric_limits<i16>::max();
    static const i16 I16_MIN = std::numeric_limits<i16>::min();
    static const i8  I8_MAX  = std::numeric_limits<i8>::max();
    static const i8  I8_MIN  = std::numeric_limits<i8>::min();

    static const f64 F64_MAX = std::numeric_limits<f64>::max();
    static const f64 F64_MIN = std::numeric_limits<f64>::min();
    static const f32 F32_MAX = std::numeric_limits<f32>::max();
    static const f32 F32_MIN = std::numeric_limits<f32>::min();

    static const u32 InvalidID = U32_MAX;
};

#endif /* VOID_CORE_COMMON_H__ */
