#pragma once

#include <glm/glm.hpp>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    template<typename T>
    class mat3 : public glm::mat<3, 3, T> {
    public:
        typedef mat3<T>             self;
        typedef glm::mat<3, 3, T>   base;

        mat3() : base(1.0f) {}
        mat3(base b) : base(b) {}
        mat3(self const &m) : base(m) {}

        self Inverse() const { return glm::inverse(*this); }
        self Transpose() const { return glm::transpose(*this); }

        self operator - () const { return *this * -1.0f; }
    };
};
