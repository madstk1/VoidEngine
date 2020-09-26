#pragma once

#include <iostream>
#include <type_traits>
#include <typeindex>
#include <VoidEngine/Core/Common.hpp>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

#define VOID_ASSERT(expr, fmt, ...) \
    Logger::Assert(expr, __FILE__, ", ", __LINE__, ": ", fmt __VA_OPT__(,) __VA_ARGS__)

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
            Assert
        };

        static Level GetLogLevel();
        static void  SetLogLevel(Level);

        __VOID_LOG_FUNC_DEF(Debug);
        __VOID_LOG_FUNC_DEF(Info);
        __VOID_LOG_FUNC_DEF(Warning);
        __VOID_LOG_FUNC_DEF(Error);
        __VOID_LOG_FUNC_DEF(Fatal, abort());

        template<typename T, typename... Ts>
        static void Assert(bool expr, T t, Ts... ts) {
            if(!(expr)) {
                Log(GetLogPrefix(Level::Assert), t, ts...);
                abort();
            }
        }

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
