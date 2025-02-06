#pragma once

#include "imgui.h"
#include "core/Window.h"
#include "core/scene/Scene.h"

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
		RenderAPI::API RenderAPI;
		uint32_t WinWidth, WinHeight;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:

		Application(const ApplicationSpecification& spec) : m_Spec(spec)
		{
			MRT_STARTUP();

			m_Scene = CreateScope<Scene>();
 			m_Window = CreateScope<Window>(spec.Title, spec.RenderAPI, spec.WinWidth, spec.WinHeight);
			s_Instance = this;
		}

		virtual ~Application();

		Window& GetWindow() { return *m_Window; }
		Scene& GetScene() { return *m_Scene; }
		RenderAPI& GetRenderer() { return *m_Renderer; }

		inline static Application& Get() { return *s_Instance; }

		//void SubmitToMainThread(const std::function<void()>& function);

		void Run();
		bool ShouldRun() { return !glfwWindowShouldClose(m_Window->GetNativeWindow()); }
		int Close();

	private:

		Scope<Window> m_Window;
		Scope<RenderAPI> m_Renderer;
		Scope<Scene> m_Scene;

		bool m_Running = true;
		bool m_Minimized = false;

		double m_LastFrameTime = 0.0f;
		double m_TimeSinceLastTick = 0.0;

	private:

		static Application* s_Instance;
		ApplicationSpecification m_Spec;

	};

}