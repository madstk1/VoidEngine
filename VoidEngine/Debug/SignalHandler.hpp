#ifndef VOID_DEBUG_SIGNALHANDLER_H__
#define VOID_DEBUG_SIGNALHANDLER_H__

#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    class SignalHandler {
    protected:
        static void Handler(i32);

    public:
        static void Initialize();
    };
};

#endif /* VOID_DEBUG_SIGNALHANDLER_H__ */
