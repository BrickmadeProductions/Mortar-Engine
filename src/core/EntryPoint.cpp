#pragma once
#include "Application.h"

extern MortarCore::Application* MortarCore::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	//Mortar::Log::Init();

	auto app = MortarCore::CreateApplication({ argc, argv });

	while (app->ShouldRun()) app->Run();

	app->Close();
	delete app;
}

