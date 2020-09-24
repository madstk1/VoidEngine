#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Misc/Singleton.hpp>

namespace VOID_NS {
    class Engine : public Singleton<Engine> {
    protected:
        Application *m_App = nullptr;

    public:
        void SetApp(Application *app) {
            m_App = std::move(app);
        }

        Application *GetApp() {
            return m_App;
        }
    };
};
