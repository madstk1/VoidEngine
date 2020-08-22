#ifndef VOID_DEBUG_LOG_H__
#define VOID_DEBUG_LOG_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <string>
#include <typeindex>
#include <VoidEngine/Core/Common.hpp>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

#define VOID_ASSERT(expr, fmt, ...)                         \
    if(!(expr)) {                                           \
        fprintf(stderr, "[ASSERT] %s,%d ", __FILE__, __LINE__);     \
        fprintf(stderr, fmt , ##__VA_ARGS__);               \
        fprintf(stderr, "\n");                              \
        abort();                                            \
    }

namespace VOID_NS {
    typedef enum {
        VOID_LOG_LEVEL_DEBUG       = (u8) 0,
        VOID_LOG_LEVEL_INFO        = (u8) 1,
        VOID_LOG_LEVEL_WARNING     = (u8) 2,
        VOID_LOG_LEVEL_ERROR       = (u8) 3,
        VOID_LOG_LEVEL_FATAL       = (u8) 4
    } LogLevel;

    class Logger {
    protected:
        static LogLevel level_;

    public:
        static LogLevel GetLogLevel();
        static void SetLogLevel(LogLevel);

        static f32 GetFramesPerSecond();
        
        static void LogFatal(const char *fmt, ...)   __attribute__ ((format(printf, 1, 2), noreturn));
        static void LogError(const char *fmt, ...)   __attribute__ ((format(printf, 1, 2)));
        static void LogWarning(const char *fmt, ...) __attribute__ ((format(printf, 1, 2)));
        static void LogInfo(const char *fmt, ...)    __attribute__ ((format(printf, 1, 2)));
        static void LogDebug(const char *fmt, ...)   __attribute__ ((format(printf, 1, 2)));

        template <typename T>
        static const char *GetClassName();
    };
};

/**
 *  TEMPLATE IMPLEMANTATIONS
 */

namespace VOID_NS {
    template <typename T>
    const char *Logger::GetClassName() {
        i32 status = -4;
        const char *mangled = typeid(T).name();

#ifdef __GNUC__
        const char *demangled = abi::__cxa_demangle(mangled, NULL, NULL, &status);
        return (status == 0) ? demangled : mangled;
#endif

        return mangled;
    }
};

#endif /* VOID_DEBUG_LOG_H__ */
