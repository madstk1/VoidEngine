#ifndef VOID_CORE_APPLICATIONINFO_H__
#define VOID_CORE_APPLICATIONINFO_H__

#include <string>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Math/Vectors.hpp>

namespace VOID_NS {
    typedef enum {
        x0 = 0, x1 = 1, x2  = 2,
        x4 = 4, x8 = 8, x16 = 16
    } MultiSampling;

    typedef enum {
        NoBuffer     = (i32) 0,
        SingleBuffer = (i32) 1,
        DoubleBuffer = (i32) 2
    } SwapInterval;

    typedef enum {
        OpenGL
    } RenderingAPI;

    struct ApplicationInfo {
        std::string Title;

        Vector2u      Size;
        Vector2i      Position;

        i32           RefreshRate;
        f32           FixedUpdateInterval;
        Color         Background;
        bool          Fullscreen;
        bool          Resizable;

        MultiSampling Sampling;
        SwapInterval  Buffering;

        RenderingAPI  API;

        static inline ApplicationInfo& GetDefault() {
            static ApplicationInfo info;

            info.Title    = "Void Application";
            info.Size     = { 800, 600 };
            info.Position = { 0,   0   };

            info.Sampling  = MultiSampling::x4;
            info.Buffering = SwapInterval::SingleBuffer;
            info.API       = RenderingAPI::OpenGL;
            
            info.RefreshRate         = 60;
            info.Background          = Color(0.13f, 0.1f, 0.1f, 1.0f);
            info.Fullscreen          = false;
            info.Resizable           = true;
            info.FixedUpdateInterval = 1.0f / 60.0f;

            return info;
        }
    };
};

#endif /* VOID_CORE_APPLICATIONINFO_H__ */
