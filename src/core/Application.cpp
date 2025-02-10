#include "Application.h"

namespace MortarCore
{
	Application* Application::s_Instance = nullptr;

	Application::~Application() {}

	//application loop logic here
	void Application::Run() 
	{
		auto startFrame = std::chrono::steady_clock::now();

		//tick the world if we are at 60 ticks elapsed
		if (m_TimeSinceLastTick >= 1.0f / 60.0f) 
		{

			m_Scene->Tick();
			
			m_CurrentTick++;
			m_TimeSinceLastTick = 0;

			m_Window->UpdateTitle();
			
		}

		//update the frame by frame method that has the last frame time as a param
		m_Scene->Update(m_LastFrameTime);
	

		//render the scene and push to the windows frame buffer
		m_Scene->Draw();
		m_Window->Push();

		auto endFrame = std::chrono::steady_clock::now();
		auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(endFrame - startFrame).count() / 1000.0 / 1000.0;

		m_LastFrameTime = static_cast<double>(frameTime);

		m_TimeSinceLastTick += m_LastFrameTime;

	}

	int Application::Close()
	{
		//destroy application context
		glfwDestroyWindow(m_Window->GetNativeWindow());
		glfwTerminate();

		MRT_PRINT_WARN("Mortar Engine is Shutting Down..");


		return 0;
	}


}