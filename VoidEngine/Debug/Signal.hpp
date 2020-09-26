#pragma once

#include <map>
#include <functional>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    class SignalHandler {
    protected:
        static void Handler(i32);

    public:
        struct Declaration {
            string name;
            std::function<void()> callback;
        };

        static void Initialize();
    };
};
