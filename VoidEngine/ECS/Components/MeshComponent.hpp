#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Misc/Mesh.hpp>

namespace VOID_NS {
    class MeshComponent : public Component {
    public:
        Mesh *mesh = nullptr;
        // Material *material = Material::GetDefault();

        MeshComponent(Mesh *mesh = nullptr) : Component() {
            this->mesh = mesh;
        }
    };
};
