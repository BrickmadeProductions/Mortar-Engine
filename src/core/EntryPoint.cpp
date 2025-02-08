#pragma once

#include "Application.h"
#include "core/component/Camera.h"
#include "core/renderer/universal/load/OBJLoader.h"
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
	//runs intializations on creation (renderer, glfw, etc.)
	auto app = new Application({ "Voxel Game",  RenderAPI::API::OPENGL, 1280, 720 });
	
	//load texture
	Ref<Texture> wood = CreateRef<Texture>("resource/DirtTexture.png", 16, 16, true);
	RenderCommands::CacheTexture(wood);

	//get default material
	Ref<Material> defaultMat = RenderCommands::GetCachedMaterial(0);

	//instantiate player
	Ref<Camera> player = app->GetScene().Instantiate<Camera>("Player");

	Ref<Model> model = OBJLoader::LoadObj("resource/Cube.obj");

	for (int i = 0; i < 1000; i++)
	{
		Ref<Entity> block = app->GetScene().Instantiate<Entity>("Block" + std::to_string(i));

		//load model
		block->LoadModel(model);
		//load material
		block->GetModel()->GetMesh()->m_Material = defaultMat;
		//load texture
		block->GetModel()->GetMesh()->m_Material->m_MainTex = wood;


		block->Transform.position = glm::vec3(GRN(-200.0f, 200.0f), GRN(-200.0f, 200.0f), GRN(-200.0f, 200.0f));
		block->Transform.rotation = glm::vec3(GRN(-360.0f, 360.0f), GRN(-360.0f, 360.0f), GRN(-360.0f, 360.0f));

		block->Transform.scale = glm::vec3(GRN(0.5f, 5.0f));
	}
	

	
	// Ref<Entity> monkey = app->GetScene().Instantiate<Entity>("Monkey");

	// //load model
	// monkey->LoadModel(OBJLoader::LoadObj("resource/Monkey.obj"));
	// //load material (0 is default material)
	// monkey->GetModel()->GetMesh()->m_Material = RenderCommands::GetCachedMaterial(0);
	// monkey->Transform.position = glm::vec3(0.0,0.0,10.0);
	// monkey->Transform.scale = glm::vec3(2.0, 2.0, 2.0);


	

	//app loop
	while (app->ShouldRun()) app->Run();
	app->Close();

	delete app;

	return 0;
}

