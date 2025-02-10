#pragma once

#include "Utils.h"
#include "imgui.h"
#include "core/Window.h"
#include "core/scene/Scene.h"
#include "core/ThreadPool.h"

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

			m_ThreadPool = CreateScope<ThreadPool>(32);
 			m_Window = CreateScope<Window>(spec.Title, spec.RenderAPI, spec.WinWidth, spec.WinHeight);
			m_Scene = CreateScope<Scene>();
			s_Instance = this;
			m_LastFrameTime = 1.0;
		}

		virtual ~Application();

		ApplicationSpecification GetAppSpec() { return m_Spec; }

		inline double GetFrameTime()
		{ 
			return m_LastFrameTime;
		}
		inline double GetFPS() { return 1.0 / m_LastFrameTime; }
		
		inline static Application& Get() { return *s_Instance; }

		inline static Window& GetWindow() { return *s_Instance->m_Window; }
		inline static Scene& GetScene() { return *s_Instance->m_Scene; }
		inline static ThreadPool& GetThreadPool() { return *s_Instance->m_ThreadPool; }

		void Initialize() { m_Scene->Awake(); }
		void Run();
		bool ShouldRun() { return !glfwWindowShouldClose(m_Window->GetNativeWindow()); }
		int Close();

	private:

		Scope<Window> m_Window;
		Scope<Scene> m_Scene;
		Scope<ThreadPool> m_ThreadPool;

		bool m_Running = true;
		bool m_Minimized = false;

		double m_LastFrameTime;

		double m_TimeSinceLastTick = 0.0;
		uint32_t m_CurrentTick = 0;


	private:

		static Application* s_Instance;
		ApplicationSpecification m_Spec;

	};

}