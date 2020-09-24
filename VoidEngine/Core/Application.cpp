#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Graphics/Renderer.hpp>

#if defined(VOID_ENABLE_OPENGL)
#include <VoidEngine/Graphics/GL/Renderer.hpp>
#endif

namespace VOID_NS {
    Application::Application(ApplicationCreationInfo info) {
        this->m_Info = info;
    }

    Application::~Application() {}
};

using namespace VOID_NS;

int main(int argc, char **argv) {
    /**
     *  Initialization
     */

    ApplicationCreationInfo defaultInfo = {};
    CreateApplication(defaultInfo);

    VOID_ASSERT(Application::Get() != nullptr, "No application has been initialized.");
    new World();

    ApplicationCreationInfo outputInfo = Application::Get()->GetInfo();

    //switch(outputInfo.API) {
        //case RenderingAPI::OpenGL:
            //new RendererGL(outputInfo);
            //break;
    //}

    /**
     *  Startup
     */

    Application::Get()->Start();
    World::Get()->Start();
}
