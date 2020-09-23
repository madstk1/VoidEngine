#ifndef VOID_RENDERING_WINDOW_H__
#define VOID_RENDERING_WINDOW_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Misc/Delegate.hpp>

namespace VOID_NS {
    class Window {
    protected:
        std::string m_Title;
        Vector2i    m_Position;
        Vector2u    m_Size;
        Color       m_Background;
        bool        m_Resizable;
        bool        m_Fullscreen;

    public:
        Delegate<std::string>   OnTitle;
        Delegate<Vector2i>      OnPosition;
        Delegate<Vector2u>      OnSize;
        Delegate<Color>         OnBackground;
        Delegate<bool>          OnResizable;
        Delegate<bool>          OnFullscreen;

        Window(ApplicationInfo info) {
            m_Title         = info.Title;
            m_Position      = info.Position;
            m_Size          = info.Size;
            m_Background    = info.Background;
            m_Resizable     = info.Resizable;
            m_Fullscreen    = info.Fullscreen;
        }

        virtual ~Window() = default;

        virtual void SetTitle(std::string) = 0;
        virtual void SetPosition(Vector2i) = 0;
        virtual void SetSize(Vector2u) = 0;
        virtual void SetBackgroundColor(Color) = 0;
        virtual void SetResizable(bool) = 0;
        virtual void SetFullscreen(bool) = 0;

        virtual std::string GetTitle()     { return m_Title; }
        virtual Vector2i GetPosition()     { return m_Position; }
        virtual Vector2u GetSize()         { return m_Size; }
        virtual Color GetBackgroundColor() { return m_Background; }
        virtual bool GetResizable()        { return m_Resizable; }
        virtual bool GetFullscreen()       { return m_Fullscreen; }

        friend class Renderer;
    };
};

#endif /* VOID_RENDERING_WINDOW_H__ */
