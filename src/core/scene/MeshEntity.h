#pragma once

#include "core/math/Math.h"
#include "RenderEntity.h"
#include "core/resource/Mesh.h"


namespace MortarCore {

	class MeshEntity3D : public RenderEntity3D
	{
	public:

		MeshEntity3D() : RenderEntity3D("MeshEntity3D"), m_Model(){}
		MeshEntity3D(std::string Name) : RenderEntity3D(Name), m_Model() {}
		virtual ~MeshEntity3D() {}

        Ref<Model>& GetModel() { return m_Model; }
		void SetModel(Ref<Model>& m) { m_Model = m; }

		void Update (double delta) override 
		{
			Transform.rotation += glm::vec3(delta, delta, delta);
		}
		void Draw() override
		{
			for (auto& mesh : m_Model->GetMeshArray()) 
			{
				
				//TODO abstract shader submits
				mesh->m_Material->m_Shader->Activate();
				mesh->m_Material->m_Shader->SetMat4(Transform.GetTransformMatrix(), "m_Model");
				mesh->m_Material->m_Shader->LinkTexture(mesh->m_Material->m_MainTex->GetTextureID(), mesh->m_Material->m_MainTex->GetTextureUnit(), "u_Texture");

				Renderer::Submit(m_VertexArray, mesh->m_Material->m_Shader, 1);

			}

		}
		//ABSTRACT LATER
		void Build() override
		{
			//Create the vertex array for this object
		 	m_VertexArray = VertexArray::Create();
			m_VertexArray->Bind();

			//build the mesh's data using the model
			for (auto& mesh: m_Model->GetMeshArray())
			{
				// DEFAULT VERTEX ATTRIBUTES \\
				
				Ref<VertexBuffer> vertexBuffer = VertexBuffer::CreateBuffer(mesh->GetVertexData().data(), uint32_t(mesh->GetVertexData().size() * sizeof(mesh->GetVertexData()[0])));
				Ref<IndexBuffer> indexBuffer = IndexBuffer::CreateBuffer(mesh->GetIndiceData().data(), uint32_t(mesh->GetIndiceData().size()));
	
				vertexBuffer->SetLayout(mesh->GetBufferLayout());

				m_VertexArray->PushVertexBuffer(vertexBuffer, 0);
				m_VertexArray->SetIndexBuffer(indexBuffer);	

			}
			m_VertexArray->Unbind();
			
		}
		
	private:

        Ref<Model> m_Model;
	};
}
