#pragma once

#include "Renderer.h"
#include "core/Application.h"
#include <glm/gtx/string_cast.hpp>

namespace MortarCore
{

    void RenderBatch::UpdateInstanceBufferData()
    {
        //push into the flat buffer
        for (int i = 0; i < m_EntityBatch.size(); i++) 
        { 
            glm::mat4 modelMatrix = m_EntityBatch[i]->Transform.GetTransformMatrix();
            float* matrixValue = glm::value_ptr(modelMatrix); // Pointer to the start of the matrix data

            // Efficiently copy 16 values from matrixValue to m_InstanceBufferData
            std::copy(matrixValue, matrixValue + 16, m_InstanceBufferData.begin() + i * 16);
           
        }

        
    }

    RenderBatch::RenderBatch(std::vector<Ref<RenderEntity>>& entityBatch) 
    : m_BatchShader(entityBatch[0]->GetModel()->GetMesh()->m_Material->m_Shader)
    {
        //this can sometimes contain only one entity

        //only runs once to batch entities so that they can be drawn in one call
        
        m_EntityBatch = entityBatch;
        m_InstanceBufferData.resize(entityBatch.size() * 16);
        m_VertexArray = VertexArray::Create(uint32_t(entityBatch.size()));
       
        /// DEFAULT VERTEX ATTRIBUTES \\\
        
        //creates render batch that can be used later for rendering
        auto& meshTemplate = m_EntityBatch[0]->GetModel()->GetMesh();
       
        Ref<VertexBuffer> vertexBuffer = VertexBuffer::CreateBuffer(meshTemplate->GetVertexData().data(), uint32_t(meshTemplate->GetVertexData().size() * sizeof(meshTemplate->GetVertexData()[0])));
        Ref<IndexBuffer> indexBuffer = IndexBuffer::CreateBuffer(meshTemplate->GetIndiceData().data(), uint32_t(meshTemplate->GetIndiceData().size()));

        //just use the first entity mesh as the buffer layout, they are all the same
        vertexBuffer->SetLayout(m_EntityBatch[0]->GetModel()->GetMesh()->GetBufferLayout());
        m_VertexArray->PushVertexBuffer(vertexBuffer, 0);

        m_VertexArray->SetIndexBuffer(indexBuffer);

        /// INSTANCE BUFFER \\\

        //instance buffer, simple layout of mat4s (for each instance that we create)
        BufferLayout InstanceBufferLayout = 
        {
            { "m_Model", ShaderElement::Vec4f },
            { "m_Model", ShaderElement::Vec4f },
            { "m_Model", ShaderElement::Vec4f },
            { "m_Model", ShaderElement::Vec4f }
        };

        //populate m_InstanceBufferData
        UpdateInstanceBufferData();
       
        Ref<VertexBuffer> instanceBuffer = VertexBuffer::CreateBuffer(m_InstanceBufferData.data(), uint32_t(m_InstanceBufferData.size() * sizeof(float)));
     
        instanceBuffer->SetLayout(InstanceBufferLayout);

        m_VertexArray->PushVertexBuffer(instanceBuffer, 1);


    }
    
    void Renderer::Submit(Ref<RenderBatch>& batch)
    {
        uint32_t totalEntities = uint32_t(batch->GetEntityBatch().size());
        //submit async task to update the instance buffer
        Application::GetThreadPool().Submit([batch] { batch->UpdateInstanceBufferData(); });

        batch->GetInstanceBuffer()->UpdateBuffer(batch->GetInstanceBufferData().data(), uint32_t(batch->GetInstanceBufferData().size() * sizeof(float)));
        
        batch->GetBatchShader()->Activate();
        batch->GetBatchShader()->SetMat4(Application::GetScene().GetCameraCurrent()->GetViewMatrix(), "m_ViewMatrix");
        batch->GetBatchShader()->SetMat4(Application::GetScene().GetCameraCurrent()->GetProjectionMatrix(), "m_Projection");

        //draw entire batch to screen at once
        RenderCommands::DrawInstanced(batch->GetVertexArray(), batch->GetVertexArray()->GetIndexBuffer()->GetIndexCount(), batch->GetVertexArray()->GetInstanceCount());
    
    }
}