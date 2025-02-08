#pragma once

#include "Utils.h"
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

 			m_Window = CreateScope<Window>(spec.Title, spec.RenderAPI, spec.WinWidth, spec.WinHeight);
			m_Scene = CreateScope<Scene>();
			s_Instance = this;

			m_Scene->Awake();
		}

		virtual ~Application();

		ApplicationSpecification GetAppSpec() { return m_Spec; }

		Window& GetWindow() { return *m_Window; }
		Scene& GetScene() { return *m_Scene; }
		
		double GetFrameTime()
		{ 
			if (m_FrameTimes.empty()) return 0.0f;
			return m_FrameTimes.back();
		}
		double GetSmoothedFrameTime() 
		{  
			if (m_FrameTimes.empty()) return 0.0f;

			double total = 0.0f;
			for (double time : m_FrameTimes) {
				total += time;
			}
			return total / m_FrameTimes.size(); 
		}
		uint32_t GetFPS() { return uint32_t(1000.0 / (GetSmoothedFrameTime() * 1000.0)); }
		
		inline static Application& Get() { return *s_Instance; }
		
		//void SubmitToMainThread(const std::function<void()>& function);

		void Run();
		bool ShouldRun() { return !glfwWindowShouldClose(m_Window->GetNativeWindow()); }
		int Close();

	private:

		Scope<Window> m_Window;
		Scope<Scene> m_Scene;

		bool m_Running = true;
		bool m_Minimized = false;

		uint32_t  m_CurrentTick = 0;

		std::deque<double> m_FrameTimes;
		double m_TimeSinceLastTick = 0.0;

	private:

		static Application* s_Instance;
		ApplicationSpecification m_Spec;

	};

}