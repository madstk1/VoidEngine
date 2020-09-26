#include <signal.h>
#include <errno.h>
#include <string.h>
#include <VoidEngine/Core/Engine.hpp>
#include <VoidEngine/Debug/Signal.hpp>

#define DEFINE_SIGNAL(sig, callback) \
    { sig, { #sig, callback } }

namespace VOID_NS {
    void ExitProxy() {
        Logger::Warning("Exit proxy.");
        Engine::Get()->Exit();
    }
    
    const std::map<i32, SignalHandler::Declaration> m_Signals = {
        DEFINE_SIGNAL(SIGHUP,   ExitProxy),
        DEFINE_SIGNAL(SIGTERM,  ExitProxy),
        DEFINE_SIGNAL(SIGINT,   ExitProxy),
        DEFINE_SIGNAL(SIGABRT,  ExitProxy),
        DEFINE_SIGNAL(SIGILL,   ExitProxy),
    };

    void SignalHandler::Initialize() {
        for(const auto &sig : m_Signals) {
            if(signal(sig.first, SignalHandler::Handler) == SIG_ERR) {
                Logger::Error("Failed to register signal ", sig.second.name, ", ", strerror(errno));
                continue;
            }

            Logger::Debug("Setup signal for ", sig.second.name);
        }
    }

    void SignalHandler::Handler(i32 code) {
        for(const auto &sig : m_Signals) {
            if(sig.first == code) {
                Logger::Warning("Caught signal: ", code, ", ", sig.second.name);
                sig.second.callback();
            }
        }
    }
};
