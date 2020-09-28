#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Linear.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class Transform {
    public:
        Transform(Vector3f position, Vector3f rotation, Vector3f scale = Vector3f(1.0f));
        virtual ~Transform() = default;

    protected:
    };
};
