#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Vector3.hpp>

namespace VOID_NS {
    template<typename T>
    class mat4 : public glm::mat<4, 4, T> {
    public:
        typedef mat4<T>             self;
        typedef glm::mat<4, 4, T>   base;

        mat4() : base(1.0f) {}
        mat4(base b) : base(b) {}
        mat4(self const &m) : base(m) {}

        self Inverse() const { return glm::inverse(*this); }
        self Transpose() const { return glm::transpose(*this); }

        self operator - () const { return *this * -1.0f; }

        static self TransformationMatrix(const vec3<f32> &position, const vec3<f32> &rotation, const vec3<f32> &scale) {
            return self(1.0f)
                + position
                * glm::rotate(self(1.0f), glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f })
                * glm::rotate(self(1.0f), glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f })
                * glm::rotate(self(1.0f), glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f })
                * glm::scale(self(1.0f), {scale.x, scale.y, scale.z});
        }

        static self PerspectiveMatrix(f32 fov, f32 aspectRatio, f32 zNear, f32 zFar) {
            return glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
        }

        static self ViewMatrix(const vec3<f32> &position, const vec3<f32> &direction) {
            return glm::lookAt(position, position + direction, {0, 1, 0});
        }
    };
};
