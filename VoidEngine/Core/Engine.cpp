#include <chrono>

#include <VoidEngine/Core/Engine.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Debug/Signal.hpp>
#include <VoidEngine/Graphics/Renderer.hpp>
#include <VoidEngine/Graphics/ShaderProcessor.hpp>
#include <VoidEngine/Misc/Translations.hpp>
#include <VoidEngine/Misc/Time.hpp>

/* OpenGL */
#include <VoidEngine/Graphics/GL/Renderer.hpp>

namespace VOID_NS {
    void Engine::SetApp(Ptr<App> app) {
        Logger::Info("Void Engine, v",
            VOID_VERSION_MAJOR, ".",
            VOID_VERSION_MINOR, ".",
            VOID_VERSION_PATCH, "."
        );

        SetDefaultSettings();

        Logger::Assert(app != nullptr, "Application is null.");
        m_App = std::move(app);
        m_API = m_App->GetAPI();

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
        switch(m_API) {
            case RenderingAPI::OpenGL: m_Renderer = new RendererGL(); break;
            case RenderingAPI::Vulkan: m_Renderer = nullptr; break;
        }
        Logger::Assert(m_Renderer != nullptr, "Renderer hasn't been initialized!");


        /**
         *  Initialization
         */

        SignalHandler::Initialize();
        ShaderProcessor::Initialize();

        m_Running = true;
        m_Renderer->Initialize();
        m_Renderer->SetCullFace(CullFace::Front);
        m_Renderer->SetFrontFace(FrontFace::CW);
        m_Renderer->SetDepthTest(DepthTest::Less);

        m_App->Start();
        World::Get()->Start();

        /**
         *  Game loop
         */

        while(m_Running) {
            m_App->Update();
            World::Get()->Update();

            m_Renderer->Clear((ClearFlag) (ClearColor | ClearDepth));
            m_Renderer->Begin();
            m_Renderer->Draw();
            m_Renderer->End();
            m_Renderer->SwapBuffers();
        }

        /**
         *  Destruction
         */

        ShaderProcessor::Destroy();
        m_Renderer->Destroy();

        return Error::NoError;
    }
    
    const f32 Engine::GetTime() const {
        return Timestep::Now().Seconds();
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
