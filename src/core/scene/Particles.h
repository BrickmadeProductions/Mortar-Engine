#pragma once

#include "core/math/Math.h"
#include "RenderEntity.h"
#include "renderer/universal/Shader.h"
#include "core/renderer/RenderCommands.h"
#include "core/scene/Loader.h"


namespace MortarCore {
	
	//this data gets set when we have the data back from the 

	struct alignas(16) Particle
	{
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 velocity;
		float opacity;
		float timeAlive;
		float isActive;

		Particle() : position(0.0), scale(1.0, 1.0, 1.0), velocity(0.0, 1.0, 0.0), timeAlive(0.0), opacity(1.0){}
		Particle(glm::vec3 startPos, glm::vec3 startScale, glm::vec3 startVelocity, float startOpcity) :  position(startPos), scale(startScale), velocity(startVelocity), opacity(startOpcity), timeAlive(0.0){}
	};

	class ParticleProcessData
    {
        public:

			ParticleProcessData(Ref<Mesh>& mesh) : m_BatchMesh(mesh) 
			{
				//set the default shader for particle computing
				m_ComputeShader = Loader::LoadResource<Shader>("resource/DefaultGPUParticle3D_ComputeShader.mres");
			}

			std::vector<Particle>& GetParticles() { return m_Particles; }

			void SetMesh(Ref<Mesh>& batchMesh) { m_BatchMesh = batchMesh; }
            Ref<Mesh>& GetBatchMesh() { return m_BatchMesh; }

            Ref<Material>& GetBatchMaterial() { return m_BatchMesh->m_Material; }
			Ref<Shader>& GetBatchShader() { return m_BatchMesh->m_Material->m_Shader; }

			Ref<Shader>& GetComputeShader() { return m_ComputeShader; }


        private:
		
			Ref<Shader> m_ComputeShader;
			Ref<ShaderStorageBuffer> m_ComputeBuffer;

			std::vector<Particle> m_Particles;
            Ref<Mesh>& m_BatchMesh;

    };

	class GPUParticles3D : public RenderEntity3D
	{
	public:

		GPUParticles3D() : RenderEntity3D("GPUParticles3D"), m_ParticleAmount(0), Randomess(1), LifeTime(5), Emitting(true), StartVelocity(0.0, 1.0, 0.0), SpawnOffset(0.1f), BillboardEnabled(false) {}
		GPUParticles3D(std::string Name) : RenderEntity3D(Name), m_ParticleAmount(0), Randomess(1), LifeTime(5), Emitting(true), StartVelocity(0.0, 1.0, 0.0), SpawnOffset(0.1f), BillboardEnabled(false)  {}
		virtual ~GPUParticles3D() {}

		void SetParticleData(Ref<ParticleProcessData>& particleData, uint32_t particleAmount) 
		{ 
			m_ParticleProcessData = particleData; 
			SetParticleCount(particleAmount);
		}
		
		void SetParticleCount(uint32_t particleAmount)
		{

			uint32_t change = particleAmount - m_ParticleAmount;
			m_ParticleAmount = particleAmount;

			if (change > 0)
			{
				
				for (uint32_t i = 0; i < change; i++) 
				{
					//generate some random starting velocites based on the original
					glm::vec3 startVelocity = glm::vec3(StartVelocity.x + MRTMath::RFloat(-Randomess, Randomess), StartVelocity.y + MRTMath::RFloat(-Randomess, Randomess), StartVelocity.z + MRTMath::RFloat(-Randomess, Randomess));
					Particle part(glm::vec3(0), glm::vec3(1.0), startVelocity, 1.0f);
					m_ParticleProcessData->GetParticles().push_back(part);
				}
			}

			//this should destroy any particles that
			m_ParticleProcessData->GetParticles().resize(particleAmount);

			// //rebuild
			// if (m_VertexArray->GetShaderStorageBuffer())
			// {
			// 	std::vector<char> flatBuffer = Buffer::Flatten<Particle>(m_ParticleProcessData->GetParticles());
			// }

		}

		//ABSTRACT LATER
		virtual void Build() override
		{

			m_VertexArray = VertexArray::Create();
			m_VertexArray->Bind();
			
			const auto& mesh = m_ParticleProcessData->GetBatchMesh();
		
			Ref<VertexBuffer> vertexBuffer = VertexBuffer::CreateBuffer(mesh->GetVertexData().data(), uint32_t(mesh->GetVertexData().size()));
			Ref<IndexBuffer> indexBuffer = IndexBuffer::CreateBuffer(mesh->GetIndiceData().data(), uint32_t(mesh->GetIndiceData().size()));

			std::vector<char> flatBuffer = Buffer::Flatten<Particle>(m_ParticleProcessData->GetParticles());
			Ref<ShaderStorageBuffer> shaderStorageBuffer = ShaderStorageBuffer::CreateBuffer(flatBuffer.data(), uint32_t(flatBuffer.size()));

			// PARTICLE VERTEX ATTRIBUTES \\

			//push vertex data
			vertexBuffer->SetLayout(mesh->GetBufferLayout());

			m_VertexArray->PushVertexBuffer(vertexBuffer, 0);
			m_VertexArray->SetShaderStorageBuffer(shaderStorageBuffer);
			m_VertexArray->SetIndexBuffer(indexBuffer);

			m_VertexArray->Unbind();

			
		}

		virtual void Draw() override
		{
			if (!Emitting) return;

			m_ParticleProcessData->GetComputeShader()->Activate(); //set compute shader uniforms
			m_VertexArray->GetShaderStorageBuffer()->Bind();
			m_ParticleProcessData->GetComputeShader()->SetFloat(float(Application::GetFrameTime()), "m_DeltaTime");
			m_ParticleProcessData->GetComputeShader()->SetFloat(Randomess, "m_Randomness");
			m_ParticleProcessData->GetComputeShader()->SetFloat(LifeTime, "m_TotalLifeTime");
			m_ParticleProcessData->GetComputeShader()->SetFloat(SpawnOffset, "m_SpawnOffset");
			m_ParticleProcessData->GetComputeShader()->SetVec3(StartVelocity, "m_StartVelocity");
			m_ParticleProcessData->GetComputeShader()->SetFloat(GravityMultiplier, "m_GravityMultiplier");

			GLuint workgroupSize = 256; // Your workgroup size
			GLuint numGroups = (m_ParticleAmount + workgroupSize - 1) / workgroupSize;  // Round up
			
			m_VertexArray->GetShaderStorageBuffer()->Dispatch(numGroups); //dispatch the compute buffer

			m_ParticleProcessData->GetBatchShader()->Activate();
			m_ParticleProcessData->GetBatchShader()->LinkTexture(m_ParticleProcessData->GetBatchMesh()->m_Material->m_MainTex->GetTextureID(), m_ParticleProcessData->GetBatchMesh()->m_Material->m_MainTex->GetTextureUnit(), "u_Texture");
			m_ParticleProcessData->GetBatchShader()->SetMat4(Transform.GetTransformMatrix(), "m_EmitterModel");
			m_ParticleProcessData->GetBatchShader()->SetBool(BillboardEnabled, "m_BillboardEnabled");

			Renderer::Submit(m_VertexArray, m_ParticleProcessData->GetBatchShader(), m_ParticleAmount);
		}

		void RegisterProperties() override
		{
			Reflection::RegisterProperty(m_ID, "Transform", VariantType::OBJECT, &Transform);
			Reflection::RegisterProperty(m_ID, "StartVelocity", VariantType::VEC3, &StartVelocity);
			
			Reflection::RegisterProperty(m_ID, "Emitting", VariantType::BOOL, &Emitting);
			Reflection::RegisterProperty(m_ID, "BillboardEnabled", VariantType::BOOL, &BillboardEnabled);

			Reflection::RegisterProperty(m_ID, "ParticleAmount", VariantType::INT, &m_ParticleAmount);

			Reflection::RegisterProperty(m_ID, "GravityMultiplier", VariantType::FLOAT, &GravityMultiplier);
			Reflection::RegisterProperty(m_ID, "Randomess", VariantType::FLOAT, &Randomess);
			Reflection::RegisterProperty(m_ID, "LifeTime", VariantType::FLOAT, &LifeTime);
			Reflection::RegisterProperty(m_ID, "SpawnOffset", VariantType::FLOAT, &SpawnOffset);


		}

		glm::vec3 StartVelocity;
		float GravityMultiplier;
		bool Emitting;
		float Randomess;
		float LifeTime;
		float SpawnOffset;
		bool BillboardEnabled;
	private:

		uint32_t m_ParticleAmount;
        Ref<ParticleProcessData> m_ParticleProcessData;
		
	};

}
