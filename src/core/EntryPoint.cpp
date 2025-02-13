#pragma once

#include "Mortar.h"
#include <random>

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

	//load shader
	Ref<Shader> DefaultSpatialShader = Loader::LoadResource<Shader>("resource/DefaultSpatial_Shader.mres");
	Ref<Shader> GPUParticleShader = Loader::LoadResource<Shader>("resource/DefaultGPUParticle3D_Shader.mres");

	//load models
	Ref<Model> DirtModel = Loader::LoadResource<Model>("resource/Cube.mres");
	Ref<Model> Plane = Loader::LoadResource<Model>("resource/Plane.mres");
	Ref<Model> WoodModel = DirtModel->MakeCopy<Model>();

	//wood
	WoodModel->GetMesh(0)->m_Material = CreateRef<Material>(DefaultSpatialShader);
	WoodModel->GetMesh(0)->m_Material->m_MainTex = WoodTexture;
	WoodModel->GetMeshArray()[0] = WoodModel->GetMeshArray()[0]->MakeCopy<Mesh>();

	//dirt
	DirtModel->GetMeshArray()[0] = DirtModel->GetMeshArray()[0]->MakeCopy<Mesh>();
	DirtModel->GetMesh(0)->m_Material = CreateRef<Material>(DefaultSpatialShader);
	DirtModel->GetMesh(0)->m_Material->m_MainTex = DirtTexture;

	//particles
	Ref<Mesh> ParticleMesh = Plane->GetMesh(0);
	ParticleMesh->m_Material = CreateRef<Material>(GPUParticleShader);
	ParticleMesh->m_Material->m_MainTex = FireParticleTexture;

	// LOAD OBJECTS \\

	//instantiate player
	Ref<Camera> player = app->GetScene().Instantiate<Camera>("Player");

	for (int i = 0; i < 1; i++)
	{
		Ref<ParticleProcessData> ParticleData = CreateRef<ParticleProcessData>(ParticleMesh);
		Ref<GPUParticles3D> Particles = app->GetScene().Instantiate<GPUParticles3D>("Particles " + std::to_string(i));
		Particles->Transform.position = glm::vec3(0.0, 0.0, 0.0);
		Particles->LifeTime = 4;
		Particles->Randomess = 2;
		Particles->StartVelocity = glm::vec3(0.0, 0.75, 0.0);
		Particles->SpawnOffset = 0.005f;
		Particles->BillboardEnabled = true;
		Particles->SetParticleData(ParticleData, 1000);

		//Particles->Transform.position = glm::vec3(MRTMath::RFloat(-100.0f, 100.0f), MRTMath::RFloat(-100.0f, 100.0f), MRTMath::RFloat(-100.0f, 100.0f));
	}

	for (int i = 0; i < 0; i++)
	{
		Ref<MeshEntity3D> Dirt = app->GetScene().Instantiate<MeshEntity3D>("Dirt " + std::to_string(i));
		Dirt->SetModel(DirtModel);
		Ref<MeshEntity3D> Wood = app->GetScene().Instantiate<MeshEntity3D>("Wood " + std::to_string(i));
		Wood->SetModel(WoodModel);
	
		Dirt->Transform.position = glm::vec3(MRTMath::RFloat(-100.0f, 100.0f), MRTMath::RFloat(-100.0f, 100.0f), MRTMath::RFloat(-100.0f, 100.0f));
		Dirt->Transform.rotation = glm::vec3(MRTMath::RFloat(-360.0f, 360.0f), MRTMath::RFloat(-360.0f, 360.0f), MRTMath::RFloat(-360.0f, 360.0f));
		Dirt->Transform.scale = glm::vec3(MRTMath::RFloat(0.5f, 5.0f));
	
		Wood->Transform.position = glm::vec3(MRTMath::RFloat(-100.0f, 10.0f), MRTMath::RFloat(-100.0f, 10.0f), MRTMath::RFloat(-100.0f, 100.0f));
		Wood->Transform.rotation = glm::vec3(MRTMath::RFloat(-360.0f, 360.0f), MRTMath::RFloat(-360.0f, 360.0f), MRTMath::RFloat(-360.0f, 360.0f));
		Wood->Transform.scale = glm::vec3(MRTMath::RFloat(0.5f, 5.0f));
	}

	

	//app loop
	app->Initialize();
	while (app->ShouldRun()) app->Run();
	app->Close();

	delete app;

	return 0;
}

