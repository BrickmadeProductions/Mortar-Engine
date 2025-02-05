#include "Application.h"

namespace MortarCore
{
	Application* s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& args) 
		: m_Renderer(args.RenderAPI), m_Window(args.Title, args.WinWidth, args.WinHeight) 
	{
		s_Instance = this;
	} 

	Application::~Application() {

		 
	}

	//application loop logic here
	void Application::Run() 
	{
		clock_t beginFrame = clock();

		//if a world is initialized, then run world functions
		if (m_World != nullptr) 
		{
			//tick the world if we are at 60 ticks elapsed
			if (m_TimeSinceLastTick >= 1.0f / 60.0f) 
			{

				m_World->Tick();

				m_TimeSinceLastTick = 0;
			}

			//update the frame by frame method that has the last frame time as a param
			m_World->Update(m_LastFrameTime);
		}

		//flip the screen buffers and render the scene
		m_Window.PushBuffer();

		clock_t endFrame = clock();

		m_LastFrameTime = endFrame - beginFrame;
		m_TimeSinceLastTick += m_LastFrameTime;
	}

	int Application::Close()
	{
		//destroy application context
		glfwDestroyWindow(m_Window.GetWindow());
		glfwTerminate();
		return 0;
	}


}