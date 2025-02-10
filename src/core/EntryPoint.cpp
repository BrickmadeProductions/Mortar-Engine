#pragma once

#include "Application.h"
#include "core/component/Camera.h"
#include "core/renderer/universal/load/Loader.h"
#include <random>

using namespace MortarCore;

float GRN(float min, float max) {
    // Random number generator (use std::random_device for non-deterministic randomization)
    std::random_device rd;  
    std::mt19937 gen(rd());  // Mersenne Twister pseudo-random generator
    std::uniform_real_distribution<float> dist(min, max);  // Uniform distribution between min and max

    return dist(gen);  // Return the random number
}

int main(int argc, char** argv)
{
	
	// INTIALIZATION \\

	//runs intializations on creation (renderer, glfw, etc.)
	auto app = new Application({ "Voxel Game",  RenderAPI::API::OPENGL, 1280, 720 });

	// LOAD RESOURCES \\

	//load texture
	Ref<Texture> wood = CreateRef<Texture>("resource/DirtTexture.png", 16, 16, true);
	RenderCommands::CacheTexture(wood);
	//get default material (the render api makes it automatically)
	Ref<Material> defaultMat = RenderCommands::GetCachedMaterial(0);
	//load mesh used for all cubes
	Ref<Model> CubeModel = OBJLoader::LoadObj("resource/Cube.obj");
	//set material properties
	CubeModel->GetMesh()->m_Material = defaultMat;
	CubeModel->GetMesh()->m_Material->m_MainTex = wood;
	
	// //load monke model
	// Ref<Model> MonkeyModel = OBJLoader::LoadObj("resource/Monkey.obj");
	// MonkeyModel->GetMesh()->m_Material = defaultMat;
	// MonkeyModel->GetMesh()->m_Material->m_MainTex = wood;
	// LOAD OBJECTS \\

	//instantiate player
	Ref<Camera> player = app->GetScene().Instantiate<Camera>("Player");

	//instantiate 1000 blocks
	Ref<RenderBatch> blockBatch = app->GetScene().InstantiateBatch<RenderEntity>("Block", CubeModel, 10000);

	//randomly set values
	for (auto& block : blockBatch->GetEntityBatch())
	{
		block->Transform.position = glm::vec3(GRN(-500.0f, 500.0f), GRN(-500.0f, 500.0f), GRN(-500.0f, 500.0f));
		block->Transform.rotation = glm::vec3(GRN(-360.0f, 360.0f), GRN(-360.0f, 360.0f), GRN(-360.0f, 360.0f));
		block->Transform.scale = glm::vec3(GRN(0.5f, 5.0f));
	}


	//app loop
	app->Initialize();
	while (app->ShouldRun()) app->Run();
	app->Close();

	delete app;

	return 0;
}

