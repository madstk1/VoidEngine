#pragma once

#include <map>
#include <functional>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    /**
     *  SignalHandler class for Void.
     *  This class handles signals, including, but not limited to:
     *    - Illegal instruction
     *    - Abort
     *    - Termination
     *
     *  See VoidEngine/Debug/Signal.cpp
     */
    class SignalHandler {
    protected:
        static void Handler(i32);

    public:
        /**
         *  Each signal must be declared with the following struct.
         *  name:       The signal name printed in the log.
         *  callback:   The function called by the handler.
         */
        struct Declaration {
            string name;
            std::function<void()> callback;
        };

        /**
         *  Initialize the default signals.
         *  See VoidEngine/Debug/Signal.cpp
         */
        static void Initialize();
    };
};
