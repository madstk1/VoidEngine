#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/ECS/Components/MeshComponent.hpp>
#include <VoidEngine/ECS/Entities/Camera.hpp>
#include <VoidEngine/Rendering/Renderer.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace VOID_NS {
    void Renderer::CalculateMVP(MVP *mvp) {
        f32 aspectRatio = (f32) g_Window->GetSize().x / (f32) g_Window->GetSize().y;
        mvp->model = glm::mat4(1.0f);
        mvp->proj  = glm::perspective(glm::radians(g_Camera->fieldOfView), aspectRatio, g_Camera->zNear, g_Camera->zFar);
        mvp->view  = glm::lookAt(g_Camera->position, g_Camera->position + g_Camera->Forward(), {0, 1, 0});
    }
};
