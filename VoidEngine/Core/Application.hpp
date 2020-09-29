#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>

namespace VOID_NS {
    /**
     *  Class that represents a user-defined application,
     *  which is used by the Engine-class.
     */
    class App {
    public:
        explicit App(string name, RenderingAPI api = RenderingAPI::OpenGL) :
            m_Name(name), m_API(api) {}

        virtual ~App() = default;

        /**
         *  Runs when the application is first initialized.
         */
        virtual void Start() {}

        /**
         *  Runs every frame.
         */
        virtual void Update() {}

        /**
         *  Runs every (1.0 / FixedUpdateInterval) seconds.
         *  See Engine-class.
         */
        virtual void FixedUpdate() {}

        /**
         *  Returns the name of the application.
         */
        inline const string &GetName() const { return m_Name; }

        /**
         *  Returns the rendering API of the application.
         */
        inline const RenderingAPI &GetAPI() const { return m_API; }

    protected:
        string m_Name;
        const RenderingAPI m_API;
    };
};
