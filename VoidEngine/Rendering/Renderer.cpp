#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/ECS/Entities/Camera.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace VOID_NS {
    static Mat4 GetRotationScaleMatrix(Entity *e) {
        return Mat4(1.0f)
            * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.x), { 1.0f, 0.0f, 0.0 })
            * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.x), { 0.0f, 1.0f, 0.0 })
            * glm::rotate(Mat4(1.0f), glm::radians(e->rotation.x), { 0.0f, 0.0f, 1.0 })
            * glm::scale(Mat4(1.0f), e->scale);
    }

    void Renderer::CalculateMVP(MVP *mvp) {
        f32 aspectRatio = (f32) g_Window->GetSize().x / (f32) g_Window->GetSize().y;
        mvp->model = glm::mat4(1.0f);
        mvp->proj  = glm::perspective(glm::radians(g_Camera->fieldOfView), aspectRatio, g_Camera->zNear, g_Camera->zFar);
        mvp->view  = glm::lookAt(g_Camera->position, g_Camera->position + g_Camera->Forward(), {0, 1, 0});
    }

    void Renderer::PopulateGeometryBuffer(GeometryBuffer *data) {
        if(!data) { return; }

        u32 indexExtension = 0;

        data->vertices.Clear();
        data->indices.Clear();

        for(Entity *e : g_World->GetEntities()) {
            MeshComponent *mc = e->GetComponent<MeshComponent>();

            if(!e->renderable || e->isStatic != (data->GetUsage() == Buffer::BufferUsage::Static) || mc == nullptr || mc->mesh == nullptr) {
                continue;
            }

            Mat4 transform = GetRotationScaleMatrix(e);
            
            for(Vertex v : mc->mesh->vertices) {
                Vector4 v4 = Vector4(v.position, 1.0f) * transform;

                v.position = Vector3(v4) + e->position;
                data->vertices.Append(v);
            }

            for(const u32 &i : mc->mesh->indices) {
                data->indices.Append(i + indexExtension);
            }

            indexExtension += mc->mesh->vertices.size();
        }
    }

    void Renderer::PopulateShaderBuffer(ShaderBuffer *data) {
        if(!data) { return; }

        data->Reset();

        for(Entity *e : g_World->GetEntities()) {
            Mesh mesh;
            MeshComponent *mc = e->GetComponent<MeshComponent>();

            if(!e->renderable || e->isStatic != (data->GetUsage() == Buffer::BufferUsage::Static) || mc == nullptr || mc->mesh == nullptr) {
                continue;
            }

            Mat4 transform = GetRotationScaleMatrix(e);
            Material *mat = (mc->material) ? mc->material : Material::GetDefault();

            mesh.vertices.clear();
            mesh.indices.clear();
            
            for(Vertex v : mc->mesh->vertices) {
                Vector4 v4 = Vector4(v.position, 1.0f) * transform;

                v.position = Vector3(v4) + e->position;
                mesh.vertices.push_back(v);
            }

            for(const u32 &i : mc->mesh->indices) {
                mesh.indices.push_back(i);
            }

            data->AppendPair(mat, mesh);
        }
    }
};
