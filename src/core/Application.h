#pragma once

#include "Utils.h"
#include "imgui.h"
#include "Window.h"
#include "core/renderer/universal/Renderer.h"
#include "core/world/World.h"

int main(int argc, char** argv);

namespace MortarCore
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		const char* Title = "Game";
		Renderer::API RenderAPI;
		int WinWidth, WinHeight;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:

		Application(const ApplicationSpecification& args);
		~Application();

		inline Window& GetWindow() { return m_Window; }
		inline Renderer& GetRenderer() { return m_Renderer; }

		inline void SetWorld(World& world) { m_World = &world; }
		inline World& GetWorld() { return *m_World; }

		inline static Application& Get() { return *s_Instance; }

		//void SubmitToMainThread(const std::function<void()>& function);

	private:

		void Run();
		bool ShouldRun() { return !glfwWindowShouldClose(m_Window.GetWindow()); }
		int Close();

	private:

		Window m_Window;
		Renderer m_Renderer;

		World* m_World;

		bool m_Running = true;
		bool m_Minimized = false;

		float m_LastFrameTime = 0.0f;
		float m_TimeSinceLastTick = 0.0;

	private:

		ApplicationSpecification m_Spec;

		friend int ::main(int argc, char** argv);
	};

	//defined by the seperate application instance using the engine
	Application* CreateApplication(ApplicationCommandLineArgs args);

}