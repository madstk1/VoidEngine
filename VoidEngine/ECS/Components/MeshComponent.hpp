#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Material.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class MeshComponent : public Component {
    public:
        Material material = Material::GetDefault();
        Vector<Vertex> vertices;
        Vector<Index> indices;

        MeshComponent(Entity *e) : Component(e) {
        }
    };
};
