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

    /**
     *  Engine class, which manages rendering, application-settings and updates.
     */
    class Engine : public Singleton<Engine> {
    public:
        /**
         *  Application settings.
         */
        GetSet<string>          Title;
        GetSet<Vector2u>        Size;
        GetSet<Vector2i>        Position;
        GetSet<Color>           BackgroundColor;
        GetSet<f32>             FixedUpdateInterval;
        GetSet<bool>            Fullscreen;
        GetSet<bool>            Resizable;
        GetSet<MultiSampling>   Sampling;
        GetSet<SwapInterval>    Buffering;

        /**
         *  Sets the current application of the engine.
         *  Must be a valid application.
         */
        void SetApp(Ptr<App>);

        /**
         *  Gets the current application of the engine.
         *  If not set, returns nullptr.
         */
        const Ptr<App> &GetApp() const;

        /**
         *  Initializes the engine and it's components.
         *  This will be a blocking method, until a exit-request is recieved.
         *  Returns Error::NoError or the appropiate error, if any.
         */
        Error Run();

        /**
         *  Returns the current state of the engine.
         */
        const bool IsRunning() const;

        /**
         *  Send exit-request to the engine.
         */
        void Exit();

        /**
         *  Gets the current run-time, in seconds.
         *  This is generally used for delta-time and FPS calculations.
         */
        const f32 GetTime() const;

        /**
         *  Gets the delta time between full-renders, in seconds.
         */
        const f32 GetDeltaTime() const;

        /**
         *  Gets the delta time, between fixed updates.
         *  Fixed delta time = 1.0 / FixedUpdateInterval
         */
        const f32 GetFixedDeltaTime() const;

        /**
         *  Gets the current FPS, based on the last full-render duration.
         */
        const f32 GetFramesPerSecond() const;

        /**
         *  Gets the current renderer, used by the engine.
         *  May return nullptr, if the engine has not been initialized.
         */
        const Renderer *GetRenderer() const { return m_Renderer; }

        /**
         *  Gets the engine's current rendering API.
         */
        const RenderingAPI GetAPI() const { return m_API; }

    protected:
        Ptr<App> m_App = nullptr;
        bool m_Running = false;

        Renderer *m_Renderer;
        RenderingAPI m_API;

        void SetDefaultSettings() {
            Title               = "Void Engine Application";
            Size                = Vector2u(800, 600);
            Position            = Vector2i(-1);
            BackgroundColor     = Color(0.1f, 0.1f, 0.1f, 1.0f);
            FixedUpdateInterval = 60.0f;
            Fullscreen          = false;
            Resizable           = true;
        }
    };
};
