#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Component.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Misc/Material.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    /**
     *  Default MeshComponent.
     *  This is used to render meshes using materials.
     */
    class MeshComponent : public Component {
    public:
        /**
         *  The component's material.
         *  This includes information on how the object looks.
         */
        Material material = Material::GetDefault();

        /**
         *  Vector of vertices, to hold all vertices of the mesh.
         */
        Vector<Vertex> vertices;

        /**
         *  Vector of indices, which are used to bind vertices together.
         */
        Vector<Index> indices;

        /**
         *  Constructor, which requires the parent entity.
         *
         *  NOTE: Parent must not be null.
         */
        MeshComponent(Entity *e) : Component(e) {
        }
    };
};
