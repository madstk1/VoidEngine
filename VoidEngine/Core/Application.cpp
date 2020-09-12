#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Debug/SignalHandler.hpp>
#include <VoidEngine/ECS/Entities/Camera.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

#if defined(VOID_ENABLE_OPENGL)
#include <VoidEngine/Platforms/GL/Renderer.hpp>
#endif

namespace VOID_NS {
    Application::Application() : Application(ApplicationInfo::GetDefault()) {}

    Application::Application(ApplicationInfo info) {
        g_FixedUpdateInterval = info.FixedUpdateInterval;
        g_World = Allocator::Allocate<World>(info);

        switch(info.API) {
#if defined(VOID_ENABLE_OPENGL)
            case RenderingAPI::OpenGL: g_Renderer = (Renderer *) Allocator::Allocate<RendererGL>(info); break;
#endif
            default: Logger::LogFatal(VOID_ERR_INV_API);
        }
    }

    Application::~Application() {
        Allocator::Free(g_Renderer);
    }

    void Application::Exit() {
        Allocator::Free(g_Application);
        exit(0);
    }

    Application     *g_Application;
    Camera          *g_Camera;
    Renderer        *g_Renderer;
    Window          *g_Window;
    World           *g_World;
    f32              g_FixedUpdateInterval;
};

int main(int argc, char **argv) {
#if defined(VOID_ENABLE_DEBUG)
    Logger::LogInfo(
        "Void Engine, v%d.%d.%d",
        VOID_VERSION_MAJOR,
        VOID_VERSION_MINOR,
        VOID_VERSION_PATCH
    );
#endif

    Void::Logger::Initialize();

    Void::ApplicationInfo k_DefaultInfo = Void::ApplicationInfo::GetDefault();
    Void::g_Application = Void::CreateApplication(k_DefaultInfo);

    Void::SignalHandler::Initialize();
    Void::g_Application->Initialize();

    ShaderLibrary::CreateDefaultShaders();

    /* This will create a Camera, and assign g_Camera. */ 
    if(!Void::g_Camera) {
        Allocator::Allocate<Camera>();
    }
    VOID_ASSERT(Void::g_Camera != nullptr, "g_Camera is nullptr.");

    Void::g_Application->Start();
    Void::g_World->Start();

    while(Void::g_Renderer->IsRunning()) {
        Void::Time::HandleDeltaTime();

        Void::g_Application->Update();
        Void::g_World->Update();

        Void::g_Renderer->Begin();
        Void::g_Renderer->Render();
        Void::g_Renderer->End();
    }
    return 0;
}
