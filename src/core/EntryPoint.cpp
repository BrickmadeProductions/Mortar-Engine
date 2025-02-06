#pragma once

#include "Application.h"

using namespace MortarCore;

int main(int argc, char** argv)
{
	ApplicationSpecification spec { "Voxel Game",  RenderAPI::API::OPENGL, 1280, 720 };

	auto app = new Application(spec);

	while (app->ShouldRun()) app->Run();

	app->Close();
	delete app;

	return 0;
}

