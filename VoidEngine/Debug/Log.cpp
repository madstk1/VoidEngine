#include <cstdarg>
#include <cstring>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    Logger::Level Logger::m_Level = Logger::Level::Warning;

    struct tm *Logger::GetTime() {
        time_t now = time(0);
        return gmtime(&now);
    }

    Logger::Level Logger::GetLogLevel() {
        return Logger::m_Level;
    }

    f32 Logger::GetFramesPerSecond() {
        return 1.0f / Time::GetDeltaTime();
    }

    u64 Logger::GetMemoryAllocations() {
        return Allocator::m_AllocatedSize;
    }
    
    void Logger::SetLogLevel(Logger::Level level) {
        Logger::m_Level = level;
    }
};
