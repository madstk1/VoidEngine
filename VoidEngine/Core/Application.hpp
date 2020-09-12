#ifndef VOID_CORE_APPLICATION_H__
#define VOID_CORE_APPLICATION_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>
#include <VoidEngine/Rendering/Window.hpp>

namespace VOID_NS {
    class Camera;

    class Application {
    public:
        Application();
        Application(ApplicationInfo);
        virtual ~Application();

        virtual void Initialize() {}
        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}

        static void Exit();

        friend int ::main(int argc, char **argv);
    };

    extern Application     *g_Application;
    extern Camera          *g_Camera;
    extern Renderer        *g_Renderer;
    extern Window          *g_Window;
    extern World           *g_World;
    extern f32              g_FixedUpdateInterval;

    extern Application *CreateApplication(ApplicationInfo);
};

#endif /* VOID_CORE_APPLICATION_H__ */
