#include <cstdarg>
#include <sstream>
#include <iomanip>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/Debug/Log.hpp>


namespace VOID_NS {
    LogLevel Logger::level_ = LogLevel::VOID_LOG_LEVEL_WARNING;
    FILE *Logger::s_Output;

    void Logger::Log(const char *prefix, const char *fmt, va_list args) {
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
    time_t now = time(0);
    struct tm *time = gmtime(&now);;
    
    std::stringstream fmt;
    fmt << std::setfill('0') << std::setw(2) << time->tm_mday;
    fmt << std::setfill('0') << std::setw(2) << time->tm_mon;
    fmt << time->tm_year - 100;
    fmt << "_";
    fmt << std::setfill('0') << std::setw(2) << time->tm_hour;
    fmt << std::setfill('0') << std::setw(2) << time->tm_min;
    fmt << std::setfill('0') << std::setw(2) << time->tm_sec;

    s_Output = fopen(("void_" + fmt.str() + ".log").c_str(), "w");
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
