#pragma once

#include "Renderer.h"
#include "core/Application.h"
#include <glm/gtx/string_cast.hpp>

namespace MortarCore
{

    void Renderer::Submit(const Ref<Entity> entity)
    {
        //MRT_PRINT(std::string(std::string("Submiting Entity To Renderer: " +  entity->Name + " Transform: ") + std::to_string(entity->Transform.position.x) + ", " + std::to_string(entity->Transform.position.y) + ", " + std::to_string(entity->Transform.position.z)));
        
        //check to be sure it has a model, mesh, and material with shader
        MRT_CORE_ASSERT(entity->GetModel());
        MRT_CORE_ASSERT(entity->GetModel()->GetMesh());
        MRT_CORE_ASSERT(entity->GetModel()->GetMesh()->m_Material);
        MRT_CORE_ASSERT(entity->GetModel()->GetMesh()->m_Material->m_Shader);

        Ref<Shader>& shader = entity->GetModel()->GetMesh()->m_Material->m_Shader;

        shader->Activate();

        shader->SetMat4(entity->Transform.GetTransformMatrix(), "m_Model");
        shader->SetMat4(Application::Get().GetScene().GetCameraCurrent()->GetViewMatrix(), "m_ViewMatrix");
        shader->SetMat4(Application::Get().GetScene().GetCameraCurrent()->GetProjectionMatrix(), "m_Projection");

        Ref<VertexArray>& vertexArray = entity->GetModel()->GetMesh()->GetVertexArray();
        MRT_CORE_ASSERT(vertexArray);

        // MRT_PRINT("Transform");
        // MRT_PRINT(glm::to_string(entity->Transform.GetTransformMatrix()));
        // MRT_PRINT("View");
        // MRT_PRINT(glm::to_string(Application::Get().GetScene().GetCameraCurrent()->GetViewMatrix()));
        // MRT_PRINT("Proj");
        // MRT_PRINT(glm::to_string(Application::Get().GetScene().GetCameraCurrent()->GetProjectionMatrix()));

        RenderCommands::DrawIndexed(vertexArray, vertexArray->GetIndexBuffer()->GetIndexCount());
    }
}