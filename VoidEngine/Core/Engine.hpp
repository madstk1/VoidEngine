#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>
#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Math/Linear.hpp>
#include <VoidEngine/Memory/Allocator.hpp>
#include <VoidEngine/Misc/GetSet.hpp>
#include <VoidEngine/Misc/Singleton.hpp>

namespace VOID_NS {
    class Renderer;

    class Engine : public Singleton<Engine> {
    public:
        /* Getters / setters */
        GetSet<string>          Title;
        GetSet<Vector2u>        Size;
        GetSet<Vector2i>        Position;
        GetSet<Color>           BackgroundColor;
        GetSet<f32>             FixedUpdateInterval;
        GetSet<bool>            Fullscreen;
        GetSet<bool>            Resizable;
        GetSet<MultiSampling>   Sampling;
        GetSet<SwapInterval>    Buffering;

        void SetApp(Ptr<App>);
        const Ptr<App> GetApp() const;

        Error Run();

        const bool IsRunning() const;
        void Exit();

        const f32 GetTime() const;
        const f32 GetDeltaTime() const;
        const f32 GetFixedDeltaTime() const;
        const f32 GetFramesPerSecond() const;

        const Renderer *GetRenderer() const { return m_Renderer; }

    protected:
        Ptr<App> m_App = nullptr;
        bool m_Running = false;

        Renderer *m_Renderer;
    };
};
