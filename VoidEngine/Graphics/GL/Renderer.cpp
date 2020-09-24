#include <VoidEngine/Graphics/GL/Renderer.hpp>
#include <VoidEngine/Graphics/GL/Helper.hpp>

namespace VOID_NS {
    RendererGL::RendererGL() {
    }

    RendererGL::~RendererGL() {
    }
    
    void RendererGL::Begin() {
    }

    void RendererGL::Draw() {
    }

    void RendererGL::End() {
    }
    
    f64 RendererGL::RenderTime() {
        return glfwGetTime();
    }

    bool RendererGL::IsRunning() {
        return !glfwWindowShouldClose(m_Window);
    }

    Vector<string> RendererGL::GetExtensions() {
        i32 nExtensions = 0;
        Vector<std::string> extensions;

        glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

        for(i32 i = 0; i < nExtensions; i++) {
            const uchar *ext = glGetStringi(GL_EXTENSIONS, i);
            extensions.Append(std::string((char *) ext));
        }
        return extensions;
    }
    
    void RendererGL::Clear(ClearFlag f) {
        u32 flag = Translate(f);
        glClear(flag);
        glClearColor(
            m_Background.r,
            m_Background.g,
            m_Background.b,
            m_Background.a
        );
    }

    /**
     *  Setters
     */

    void RendererGL::SetTitle(std::string title) {
        m_Title = title;
        glfwSetWindowTitle(m_Window, title.c_str());
    }
    
    void RendererGL::SetSize(Vector2u size) {
        m_Size = size;
        glfwSetWindowSize(this->m_Window, size.x, size.y);
    }
    
    void RendererGL::SetPosition(Vector2i pos) {
        m_Position = pos;
        glfwSetWindowPos(this->m_Window, pos.x, pos.y);
    }
    
    void RendererGL::SetMaxFPS(i32 fps) {
        m_MaxFPS = fps;
        glfwWindowHint(GLFW_REFRESH_RATE, (fps == -1) ? GLFW_DONT_CARE : fps);
    }
    
    void RendererGL::SetBackground(Color bg) {
        m_Background = bg;
    }
    
    void RendererGL::SetFullscreen(bool fs) {
        m_Fullscreen = fs;
        glfwSetWindowMonitor(
            this->m_Window,
            (fs) ? this->m_Monitor : nullptr,
            GetPosition().x, GetPosition().y,
            GetSize().x,     GetSize().y,
            GetMaxFPS()
        );
    }
    
    void RendererGL::SetResizable(bool rs) {
        m_Resizable = rs;
        glfwWindowHint(GLFW_RESIZABLE, rs);
    }
    
    void RendererGL::SetSampling(MultiSampling samples) {
        /* NOTE: OpenGL does not like a sample-count of 0, in glTexImage2DMultisample. */
        m_Sampling = ((u32) samples > 1) ? samples : (MultiSampling) 1;

        /* In case no renderbuffer is found, don't update it. */
        i32 rbBinding = 0;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &rbBinding);

        if(rbBinding != 0) {
            SetSize(GetSize());
        }
    }
    
    void RendererGL::SetBuffering(SwapInterval buffering) {
        m_Buffering = buffering;
        glfwWindowHint(GLFW_DOUBLEBUFFER, m_Buffering == SwapInterval::Double);
        glfwSwapInterval((u32) m_Buffering);
    }
    
    void RendererGL::SetCulling(CullFace face) {
        m_Culling = face;

        if(face != CullFace::Disabled) {
            glEnable(GL_CULL_FACE);
            glCullFace(Translate(face));
        } else {
            glDisable(GL_CULL_FACE);
        }
    }
    
    void RendererGL::SetDepthTestFunc(DepthTest depth) {
        m_DepthTestFunc = depth;

        if(depth != DepthTest::Disabled) {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(Translate(depth));
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }
};
