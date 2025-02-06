#include "Application.h"

namespace MortarCore
{
	Application* Application::s_Instance = nullptr;

	Application::~Application() {}

	//application loop logic here
	void Application::Run() 
	{
		clock_t beginFrame = clock();

		//if a world is initialized, then run world functions
		if (m_Scene != nullptr) 
		{
			//tick the world if we are at 60 ticks elapsed
			if (m_TimeSinceLastTick >= 1.0f / 60.0f) 
			{

				m_Scene->Tick();

				m_TimeSinceLastTick = 0;
			}

			//update the frame by frame method that has the last frame time as a param
			m_Scene->Update(m_LastFrameTime);
		}

		//render the scene and push to the windows frame buffer
		m_Scene->Draw();
		m_Window->Push();

		clock_t endFrame = clock();

		m_LastFrameTime = double(endFrame - beginFrame);
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