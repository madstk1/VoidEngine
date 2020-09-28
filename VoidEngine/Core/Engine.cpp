#include <VoidEngine/Core/Engine.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Debug/Signal.hpp>
#include <VoidEngine/Graphics/Renderer.hpp>
#include <VoidEngine/Graphics/ShaderProcessor.hpp>
#include <VoidEngine/Misc/Delta.hpp>
#include <VoidEngine/Misc/Translations.hpp>

#if defined(VOID_ENABLE_OPENGL)
#include <VoidEngine/Graphics/GL/Renderer.hpp>
#endif

namespace VOID_NS {
    void Engine::SetApp(Ptr<App> app) {
        /** 
         *  Set default application settings.
         */

        this->Title.Set("Void Engine Application");
        this->Size.Set(Vector2u(800, 600));
        this->Position.Set(Vector2i(-1));
        this->BackgroundColor.Set(Color(0.1f, 0.1f, 0.1f, 1.0f));
        this->Fullscreen.Set(false);
        this->Resizable.Set(true);;

        Logger::Assert(app != nullptr, "Application is null.");
        m_App = std::move(app);
        m_API = m_App->GetAPI();

        Logger::Info("Void Engine, v",
            VOID_VERSION_MAJOR, ".",
            VOID_VERSION_MINOR, ".",
            VOID_VERSION_PATCH, "."
        );

        switch(m_API) {
#if defined(VOID_ENABLE_OPENGL)
            case RenderingAPI::OpenGL:
                m_Renderer = new RendererGL();
                break;
#endif
            case RenderingAPI::Vulkan:
                break;

            default:
                break;
        }
        Logger::Assert(m_Renderer != nullptr, "Renderer hasn't been initialized!");

        /* Re-run callbacks, just for measure. */
        this->Title.OnChange(this->Title.Get());
        this->Size.OnChange(this->Size.Get());
        this->Position.OnChange(this->Position.Get());
        this->BackgroundColor.OnChange(this->BackgroundColor.Get());
        this->Fullscreen.OnChange(this->Fullscreen.Get());
        this->Resizable.OnChange(this->Resizable.Get());
    }

    const Ptr<App> Engine::GetApp() const {
        return m_App;
    }

    const bool Engine::IsRunning() const {
        return m_Running;
    }

    void Engine::Exit() {
        Logger::Info("Received Exit request.");
        m_Running = false;
    }

    Error Engine::Run() {
        /**
         *  Initialization
         */

        m_Running = true;

        SignalHandler::Initialize();
        ShaderProcessor::Initialize();
        m_Renderer->Initialize();

        m_App->Start();
        World::Get()->Start();

        /**
         *  Game loop
         */

        while(m_Running) {
            m_App->Update();
            World::Get()->Update();

            m_Renderer->Render();
        }

        /**
         *  Destruction
         */

        ShaderProcessor::Destroy();
        m_Renderer->Destroy();

        return Error::NoError;
    }
    
    const f32 Engine::GetTime() const {
        if(GetRenderer() != nullptr) {
            return GetRenderer()->GetTime();
        }
        return 0.0f;
    }
    
    const f32 Engine::GetDeltaTime() const {
        static Delta delta;

        delta.Update();
        return delta.Difference();
    }
    
    const f32 Engine::GetFixedDeltaTime() const {
        return 1.0f / FixedUpdateInterval.Get();
    }

    const f32 Engine::GetFramesPerSecond() const {
        return 1.0f / this->GetDeltaTime();
    }
};
