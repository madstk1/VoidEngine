#include <signal.h>
#include <unordered_map>
#include <functional>

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Debug/SignalHandler.hpp>

namespace VOID_NS {
    typedef struct {
        std::string name;
        std::function<void()> handler;
    } SignalDeclaration;

    static const std::unordered_map<i32, SignalDeclaration> m_AvailableSignals = {
        {SIGHUP,    {"SIGHUP",  Application::Exit}},
        {SIGTERM,   {"SIGTERM", Application::Exit}},
        {SIGINT,    {"SIGINT",  Application::Exit}},
        {SIGABRT,   {"SIGABRT", Application::Exit}},
        {SIGILL,    {"SIGILL",  Application::Exit}},
        {SIGSEGV,   {"SIGSEGV", Application::Exit}},
    };

    void SignalHandler::Initialize() {
        for(const std::pair<i32, SignalDeclaration> sig : m_AvailableSignals) {
            signal(sig.first, SignalHandler::Handler);
            Logger::Debug("Setup signal for ", sig.second.name.c_str());
        }
    }

    void SignalHandler::Handler(i32 code) {
        for(const std::pair<i32, SignalDeclaration> sig : m_AvailableSignals) {
            if(sig.first == code) {
                Logger::Warning("Caught signal: ", code, sig.second.name.c_str());
                sig.second.handler();
            }
        }
    }
};
