#include <cstdarg>
#include <cstring>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    LogLevel Logger::level_ = LogLevel::VOID_LOG_LEVEL_WARNING;
    FILE *Logger::s_Output;

    struct tm *Logger::GetTime() {
        time_t now = time(0);
        return gmtime(&now);
    }

    void Logger::Log(const char *prefix, const char *fmt, va_list args) {
        struct tm *time = GetTime();

        fprintf(s_Output, "[%02d:%02d:%02d] ", time->tm_hour, time->tm_min, time->tm_sec);
        fprintf(s_Output, "[%s] ", prefix);
        vfprintf(s_Output, fmt, args);
        fprintf(s_Output, "\n");
    }

    LogLevel Logger::GetLogLevel() {
        return Logger::level_;
    }

    f32 Logger::GetFramesPerSecond() {
        return 1.0f / Time::GetDeltaTime();
    }

    u64 Logger::GetMemoryAllocations() {
        return Allocator::m_AllocatedSize;
    }
    
    void Logger::SetLogLevel(LogLevel level) {
        Logger::level_ = level;
    }

    void Logger::Initialize() {
#if defined(VOID_ENABLE_DEBUG)
    s_Output = stdout;
#else
    char fmt[23];
    struct tm *time = GetTime();

    // Format: void_DDMMYY_HHMMSS.log
    snprintf(
        fmt,
        23,
        "void_%02d%02d%02d_%02d%02d%02d.log",
        time->tm_mday,
        time->tm_mon,
        time->tm_year - 100,
        time->tm_hour,
        time->tm_min,
        time->tm_sec
    );
    
    s_Output = fopen(fmt, "w");
#endif
    }

    void Logger::Free() {
#if ! defined(VOID_ENABLE_DEBUG)
        fclose(s_Output);
#endif
    }
    
    void Logger::LogFatal(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_FATAL) {
            va_list args;
            va_start(args, fmt);
            Log("FATAL", fmt, args);
            va_end(args);
        }
        exit(-1);
    }
    
    void Logger::LogError(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_ERROR) {
            va_list args;
            va_start(args, fmt);
            Log("ERROR", fmt, args);
            va_end(args);
        }
    }
    
    void Logger::LogWarning(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_WARNING) {
            va_list args;
            va_start(args, fmt);
            Log("WARNING", fmt, args);
            va_end(args);
        }
    }
    
    void Logger::LogInfo(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_INFO) {
            va_list args;
            va_start(args, fmt);
            Log("INFO", fmt, args);
            va_end(args);
        }
    }
    
    void Logger::LogDebug(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_DEBUG) {
            va_list args;
            va_start(args, fmt);
            Log("DEBUG", fmt, args);
            va_end(args);
        }
    }
};
