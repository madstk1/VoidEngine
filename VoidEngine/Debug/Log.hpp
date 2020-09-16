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

namespace VOID_NS {
    class Logger {
    protected:
        template<typename T>
        static void Log(T t) {
            std::cout << t << std::endl;
        }

        template<typename T, typename ... Ts>
        static void Log(T t, Ts... ts) {
            std::cout << t;
            Log(std::forward<Ts>(ts)...);
        }

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

        template<typename T, typename... Ts> static void Debug   (T t, Ts... ts) { if(GetLogLevel() >= Level::Debug)   { Log(t, ts...); } }
        template<typename T, typename... Ts> static void Info    (T t, Ts... ts) { if(GetLogLevel() >= Level::Info)    { Log(t, ts...); } }
        template<typename T, typename... Ts> static void Warning (T t, Ts... ts) { if(GetLogLevel() >= Level::Warning) { Log(t, ts...); } }
        template<typename T, typename... Ts> static void Error   (T t, Ts... ts) { if(GetLogLevel() >= Level::Error)   { Log(t, ts...); } }
        template<typename T, typename... Ts> static void Fatal   (T t, Ts... ts) { if(GetLogLevel() >= Level::Fatal)   { Log(t, ts...); abort(); } }
        
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
    };
};

#endif /* VOID_DEBUG_LOG_H__ */
