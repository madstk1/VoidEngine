#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/UUID.hpp>

namespace VOID_NS {
    /**
     *  Simple resource class.
     *  This inherits UUID, so every resource has a unique identifier.
     */
    class Resource : public UUID {
    public:
        Resource() : UUID() {
        }
    };
};
