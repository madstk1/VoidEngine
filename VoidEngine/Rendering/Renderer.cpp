#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace VOID_NS {
    void Renderer::UpdateBufferImpl(BufferData *data, bool updateStatic) {
        if(!data) { return; }

        u32 vertexOffset = 0;
        u32 indexOffset = 0;
        u32 indexExtension = 0;

        data->vertices.clear();
        data->indices.clear();

        for(Entity *e : g_World->GetEntities()) {
            MeshComponent *mc = e->GetComponent<MeshComponent>();

            if(!e->renderable || e->isStatic != updateStatic || mc == nullptr || mc->mesh == nullptr) {
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
                data->vertices.push_back(v);
            }

            for(const u32 &i : mc->mesh->indices) {
                data->indices.push_back(i + indexExtension);
            }

            indexExtension += mc->mesh->vertices.size();

            vertexOffset += sizeof(Vertex) * mc->mesh->vertices.size();
            indexOffset  += sizeof(u32)    * mc->mesh->indices.size();
        }
    }

    void Renderer::Prepare() {
    }

    void Renderer::UpdateBuffers(BufferData *data) {
        if(!data) { return; }

        UpdateBufferImpl(data, false);
    }

    void Renderer::UpdateStaticBuffers(BufferData *data) {
        if(!data) { return; }

        UpdateBufferImpl(data, true);
    }
};
