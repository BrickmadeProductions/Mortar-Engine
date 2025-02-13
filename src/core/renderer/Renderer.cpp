#pragma once

#include "Renderer.h"
#include "core/Application.h"
#include <glm/gtx/string_cast.hpp>

namespace MortarCore
{

    void Renderer::Submit(Ref<VertexArray>& vertexArray, Ref<Shader>& shader, uint32_t instanceCount)
    {
    
        shader->Activate();

        shader->SetMat4(Application::GetScene().GetCameraCurrent()->GetViewMatrix(), "m_ViewMatrix");
        shader->SetMat4(Application::GetScene().GetCameraCurrent()->GetProjectionMatrix(), "m_Projection");

        RenderCommands::DrawInstanced(vertexArray, vertexArray->GetIndexBuffer()->GetIndexCount(), instanceCount);
      
        shader->DeActivate();


    }
}