#ifndef VOID_DEBUG_LOG_H__
#define VOID_DEBUG_LOG_H__

#include <iostream>
#include <type_traits>
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

#define __VOID_LOG_FUNC_DEF(lvl, ...)                               \
    template<typename T, typename... Ts>                            \
    static void lvl (T t, Ts... ts) {                               \
        if(GetLogLevel() <= Level::lvl) {                           \
            Log(GetLogPrefix(Level::lvl), t, ts...); __VA_ARGS__;   \
        }                                                           \
    }

namespace VOID_NS {
    class Logger {
    public:
        enum class Level {
            Debug,
            Info,
            Warning,
            Error,
            Fatal,
        };

        static Level GetLogLevel();
        static void  SetLogLevel(Level);

        static f32 GetFramesPerSecond();
        static u64 GetMemoryAllocations();


        __VOID_LOG_FUNC_DEF(Debug);
        __VOID_LOG_FUNC_DEF(Info);
        __VOID_LOG_FUNC_DEF(Warning);
        __VOID_LOG_FUNC_DEF(Error);
        __VOID_LOG_FUNC_DEF(Fatal, abort());

        template <typename T>
        static const char *GetClassName() {
            i32 status = -4;
            const char *mangled = typeid(T).name();
    
#ifdef __GNUC__
            const char *demangled = abi::__cxa_demangle(mangled, NULL, NULL, &status);
            return (status == 0) ? demangled : mangled;
#endif
            return mangled;
        }

    protected:
        static Level m_Level;
        static struct tm *GetTime();
        static std::string GetLogPrefix(Level);

        template<typename T>
        static void Log(T t) {
            std::cout << t << std::endl;
        }

        template<typename T, typename ... Ts>
        static void Log(T t, Ts... ts) {
            std::cout << t;
            Log(std::forward<Ts>(ts)...);
        }
    };
};

#endif /* VOID_DEBUG_LOG_H__ */
