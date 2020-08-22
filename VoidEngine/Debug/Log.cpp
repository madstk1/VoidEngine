#include <cstdarg>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/Debug/Log.hpp>

static void Log_(const char *prefix, const char *fmt, va_list args) {
    printf("[%s] ", prefix);
    vprintf(fmt, args);
    printf("\n");
}

namespace VOID_NS {
    LogLevel Logger::level_ = LogLevel::VOID_LOG_LEVEL_WARNING;

    LogLevel Logger::GetLogLevel() {
        return Logger::level_;
    }

    f32 Logger::GetFramesPerSecond() {
        return 1.0f / Time::GetDeltaTime();
    }
    
    void Logger::SetLogLevel(LogLevel level) {
        Logger::level_ = level;
    }
    
    void Logger::LogFatal(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_FATAL) {
            va_list args;
            va_start(args, fmt);
            Log_("FATAL", fmt, args);
            va_end(args);
        }
        exit(-1);
    }
    
    void Logger::LogError(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_ERROR) {
            va_list args;
            va_start(args, fmt);
            Log_("ERROR", fmt, args);
            va_end(args);
        }
    }
    
    void Logger::LogWarning(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_WARNING) {
            va_list args;
            va_start(args, fmt);
            Log_("WARNING", fmt, args);
            va_end(args);
        }
    }
    
    void Logger::LogInfo(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_INFO) {
            va_list args;
            va_start(args, fmt);
            Log_("INFO", fmt, args);
            va_end(args);
        }
    }
    
    void Logger::LogDebug(const char *fmt, ...) {
        if(GetLogLevel() <= VOID_LOG_LEVEL_DEBUG) {
            va_list args;
            va_start(args, fmt);
            Log_("DEBUG", fmt, args);
            va_end(args);
        }
    }
};
