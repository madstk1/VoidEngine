#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Time.hpp>

namespace VOID_NS {
    f32 Time::m_Time;
    f32 Time::m_LastTime;
    f32 Time::m_Timestep;
    f32 Time::m_FixedTimestep;
    
    void Time::HandleDeltaTime() {
        Time::m_Time = g_Renderer->GetRenderTime();
        Time::m_Timestep = Time::m_Time - Time::m_LastTime;
        Time::m_LastTime = Time::m_Time;

        // Handle fixed delta time. 
        Time::m_FixedTimestep += Time::m_Timestep;
        if(Time::m_FixedTimestep >= Time::m_FixedTimestep) {
            Time::m_FixedTimestep = 0.0f;

            g_Application->FixedUpdate();
            g_World->FixedUpdate();
        }
    }

    f32 Time::GetTime() {
        return Time::m_Time;
    }
    
    f32 Time::GetDeltaTime() {
        return Time::m_Timestep;
    }

    f32 Time::GetFixedDeltaTime() {
        return g_FixedUpdateInterval;
    }
};
