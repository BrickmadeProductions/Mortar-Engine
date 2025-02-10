#pragma once

#include "Utils.h"
#include "core/scene/RenderEntity.h"
#include "core/renderer/universal/VertexArray.h"
#include "core/renderer/universal/Material.h"

namespace MortarCore
{
    class RenderBatch
    {
        public:

            RenderBatch(std::vector<Ref<RenderEntity>>& renderEntities);

            //Currently only supports transforms, updates the entities and returns m_InstanceBufferData
            inline void UpdateInstanceBufferData();

            Ref<VertexArray>& GetVertexArray() { return m_VertexArray; }
            std::vector<Ref<RenderEntity>>& GetEntityBatch() { return m_EntityBatch; }

            std::vector<float> GetInstanceBufferData() { return m_InstanceBufferData; }
            
            //0 is for the basic vertex data
            Ref<VertexBuffer> GetInstanceBuffer() { return m_VertexArray->GetVertexBuffers()[1]; }
            Ref<Shader> GetBatchShader() { return m_BatchShader; }

        private:
        
            Ref<Shader> m_BatchShader;

            std::vector<float> m_InstanceBufferData;

            std::vector<Ref<RenderEntity>> m_EntityBatch;
            Ref<VertexArray> m_VertexArray;

    };

    class Renderer
    {        
    public:

        static void Submit(Ref<RenderBatch>& batch);
    };
   

}