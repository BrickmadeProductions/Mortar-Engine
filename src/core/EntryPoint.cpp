#pragma once

#include "Mortar.h"
#include <random>
#include "core/math/Math.h"

using namespace MortarCore;

int main(int argc, char** argv)
{
	// INTIALIZATION \\

	//runs intializations on creation (renderer, glfw, etc.)
	auto app = new Application({ "Voxel Game",  RenderAPI::API::OPENGL, 1280, 720 });

	// LOAD RESOURCES \\

	//load texture
	Ref<Texture> DirtTexture = Loader::LoadResource<Texture>("resource/DirtTexture.mres");
	Ref<Texture> WoodTexture = Loader::LoadResource<Texture>("resource/WoodTexture.mres");
	Ref<Texture> FireParticleTexture = Loader::LoadResource<Texture>("resource/FireTexture.mres");

	Ref<Texture> CampfireWoodTexture = Loader::LoadResource<Texture>("resource/CampfireWoodTexture.mres");

	//load shader
	Ref<Shader> DefaultSpatialShader = Loader::LoadResource<Shader>("resource/DefaultSpatial_Shader.mres");
	//Ref<Shader> GPUParticleShader = Loader::LoadResource<Shader>("resource/DefaultGPUParticle3D_Shader.mres");

	//load models
	Ref<Model> DirtModel = Loader::LoadResource<Model>("resource/Cube.mres");
	Ref<Model> Plane = Loader::LoadResource<Model>("resource/Plane.mres");
	Ref<Model> WoodModel = DirtModel->MakeCopy<Model>();

	//Ref<Model> CampfireModel = Loader::LoadResource<Model>("resource/CampfireModel.mres");

	//campfire
	// CampfireModel->GetMesh(0)->m_Material = CreateRef<Material>(DefaultSpatialShader);
	// CampfireModel->GetMesh(0)->m_Material->m_MainTex = CampfireWoodTexture;

	//wood
	WoodModel->GetMesh(0)->m_Material = CreateRef<Material>(DefaultSpatialShader);
	WoodModel->GetMesh(0)->m_Material->m_MainTex = WoodTexture;
	WoodModel->GetMeshArray()[0] = WoodModel->GetMeshArray()[0]->MakeCopy<Mesh>();

	//dirt
	DirtModel->GetMeshArray()[0] = DirtModel->GetMeshArray()[0]->MakeCopy<Mesh>();
	DirtModel->GetMesh(0)->m_Material = CreateRef<Material>(DefaultSpatialShader);
	DirtModel->GetMesh(0)->m_Material->m_MainTex = DirtTexture;

	//particles
	// Ref<Mesh> ParticleMesh = Plane->GetMesh(0);
	// ParticleMesh->m_Material = CreateRef<Material>(GPUParticleShader);
	// ParticleMesh->m_Material->m_MainTex = FireParticleTexture;

	// LOAD OBJECTS \\

	//instantiate player
	Ref<Camera> player = app->GetScene().Instantiate<Camera>("Player");

	//instantiate campfire
	// Ref<MeshEntity3D> Campfire = app->GetScene().Instantiate<MeshEntity3D>("Campfire");
	// Campfire->SetModel(CampfireModel);
	// Campfire->Transform.scale = glm::vec3(7.0, 7.0, 7.0);

	// for (int i = 0; i < 1; i++)
	// {
	// 	Ref<ParticleProcessData> ParticleData = CreateRef<ParticleProcessData>(ParticleMesh);
	// 	Ref<GPUParticles3D> Particles = app->GetScene().Instantiate<GPUParticles3D>("Particles " + std::to_string(i));
	// 	Particles->Transform.position = glm::vec3(0.0, 0.0, 0.0);
	// 	Particles->LifeTime = 5;
	// 	Particles->Randomess = 10.0f;
	// 	Particles->StartVelocity = glm::vec3(0.0, 25.0f, 0.0);
	// 	Particles->GravityMultiplier = -0.001f;
	// 	Particles->SpawnOffset = 0.025f;
	// 	Particles->BillboardEnabled = true;
	// 	Particles->SetParticleData(ParticleData, 100000);
	// }

	for (int i = 0; i < 500; i++)
	{
		auto entity = app->GetScene().Instantiate<MeshEntity3D>("Block " + std::to_string(i));

		entity->SetModel(i % 2 == 0 ? WoodModel : DirtModel);

		entity->Transform.position = glm::vec3(MRTMath::RFloat(-200.0, 200.0), MRTMath::RFloat(-200.0, 200.0), MRTMath::RFloat(-200.0, 200.0));
		entity->Transform.rotation = glm::vec3(MRTMath::RFloat(-180.0, 180.0), MRTMath::RFloat(-180.0, 180.0), MRTMath::RFloat(-180.0, 180.0));
		float scale = MRTMath::RFloat(1.0, 5.0);
		
		entity->Transform.scale = glm::vec3(scale, scale, scale);
	}


	//app loop
	app->Initialize();
	while (app->ShouldRun()) app->Run();
	app->Close();

	delete app;

	return 0;
}

