#ifndef VOID_CORE_TIME_H__
#define VOID_CORE_TIME_H__

#include <VoidEngine/Core/Common.hpp>

extern int main(int argc, char **argv);

namespace VOID_NS {
    class Time {
    private:
    protected:
        static f32 m_Time;
        static f32 m_LastTime;
        static f32 m_Timestep;
        static f32 m_FixedTimestep;

        static void HandleDeltaTime();

        friend int ::main(int, char *[]);

    public:
        static f32 GetTime();
        static f32 GetDeltaTime();
        static f32 GetFixedDeltaTime();
    };
};

#endif /* VOID_CORE_TIME_H__ */
