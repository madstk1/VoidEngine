#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>

namespace VOID_NS {
    class App {
    public:
        App(string name, RenderingAPI api = RenderingAPI::OpenGL) :
            m_Name(name), m_API(api) {}

        virtual ~App() = default;

        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}

        inline string GetName() { return m_Name; }
        inline RenderingAPI GetAPI() { return m_API; }

    protected:
        string m_Name;
        const RenderingAPI m_API;
    };
};
