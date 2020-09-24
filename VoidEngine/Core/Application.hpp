#pragma once

#include <string>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Graphics/RenderTypes.hpp>

namespace VOID_NS {
    class Application {
    protected:
    public:
        Application();
        virtual ~Application();

        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}
    };

    extern Application *CreateApplication();
};
