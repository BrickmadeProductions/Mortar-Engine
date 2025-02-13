#include "Application.h"

namespace MortarCore
{
	//target fps
	const double frameDuration = 1.0 / 280.0;

	Application* Application::s_Instance = nullptr;

	Application::~Application() {}

	//application loop logic here
	void Application::Run() 
	{
		MRT_PROF();
		auto frameStart = std::chrono::steady_clock::now();

		RenderCommands::GetRenderAPI()->PreFrame();

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

		ImGui::Begin("Debug Info");
		ImGui::Text((std::to_string(GetFPS()) + " FPS ").data());
		ImGui::Text((std::to_string(GetFrameTime()) + " ms ").data());

		Transform& CameraTransform = Scene::GetCameraCurrent()->Transform;
		ImGui::Text(("Camera Location: " + std::to_string(CameraTransform.position.x) + ", " + std::to_string(CameraTransform.position.y) + ", " + std::to_string(CameraTransform.position.z)).data());
		ImGui::Text(("Camera Rotation: " + std::to_string(CameraTransform.rotation.x) + ", " + std::to_string(CameraTransform.rotation.y) + ", " + std::to_string(CameraTransform.rotation.z)).data());
		ImGui::End();

		RenderCommands::GetRenderAPI()->PostFrame();

		m_Window->Push();

		//game loop ends here, everything after makes the thread sleep or does frame time calculations (abstract later)
		auto frameEnd = std::chrono::steady_clock::now();
		auto frameTime = std::chrono::duration<double>(frameEnd - frameStart).count(); // / 1.0e6 because we are using microseconds, get seconds

		double sleepTime = frameDuration - frameTime;
		//sleep if we arent at the frame limit yet
		if (sleepTime > 0)
		{ 
			auto targetTime = std::chrono::steady_clock::now() + std::chrono::duration<double>(sleepTime);
			while (std::chrono::steady_clock::now() < targetTime) continue;
		}

		m_LastFrameTime = sleepTime < 0 ? frameTime : frameTime + sleepTime;
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