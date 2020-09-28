#pragma once

#include <glm/glm.hpp>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    template<typename T>
    class mat2 : public glm::mat<2, 2, T> {
    public:
        typedef mat2<T>             self;
        typedef glm::mat<2, 2, T>   base;

        mat2() : base(1.0f) {}
        mat2(base b) : base(b) {}
        mat2(self const &m) : base(m) {}

        self Inverse() const { return glm::inverse(*this); }
        self Transpose() const { return glm::transpose(*this); }

        self operator - () const { return *this * -1.0f; }
    };
};
