#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace VOID_NS {
    void Renderer::UpdateGeometryBuffer(GeometryBuffer *data) {
        if(!data) { return; }

        u32 vertexOffset = 0;
        u32 indexOffset = 0;
        u32 indexExtension = 0;

        data->vertices.Clear();
        data->indices.Clear();

        std::vector<Shader *> shaders;

        for(Entity *e : g_World->GetEntities()) {
            MeshComponent *mc = e->GetComponent<MeshComponent>();

            if(!e->renderable || e->isStatic != (data->GetUsage() == Buffer::BufferUsage::Static) || mc == nullptr || mc->mesh == nullptr || mc->shader == nullptr) {
                continue;
            }

            Mat4 transform = Mat4(1.0f)
                * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.x), { 1.0f, 0.0f, 0.0 })
                * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.x), { 0.0f, 1.0f, 0.0 })
                * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.x), { 0.0f, 0.0f, 1.0 })
                * glm::scale(Mat4(1.0f), e->scale);
            
            for(Vertex v : mc->mesh->vertices) {
                Vector4 v4 = Vector4(v.position, 1.0f) * transform;

                v.position = Vector3(v4) + e->position;
                data->vertices.Append(v);
            }

            for(const u32 &i : mc->mesh->indices) {
                data->indices.Append(i + indexExtension);
            }

            indexExtension += mc->mesh->vertices.size();

            vertexOffset += sizeof(Vertex) * mc->mesh->vertices.size();
            indexOffset  += sizeof(u32)    * mc->mesh->indices.size();
        }
    }

    void Renderer::UpdateShaderBuffer(ShaderBuffer *data) {
    }
};
