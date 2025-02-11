#include "Window.h"
#include "core/renderer/RenderCommands.h"
#include "Application.h"
#include "core/cpuprof.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"

namespace MortarCore {

	Window::Window(const char* t, RenderAPI::API renderAPI, const uint32_t w, const uint32_t h) : title(*t), windowWidth(w), windowHeight(h)
	{		
		//Init GLFW
		MRT_CORE_ASSERT(glfwInit());

		//Tell GLFW versions
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		// TODO: remove OPENGL specific
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		glfwwindow = glfwCreateWindow(windowWidth, windowHeight, t, NULL, NULL);

		//Check for errors
		if (glfwwindow == NULL) {

			MRT_PRINT_ERR("glfw Window Creation Failed!...")
			glfwTerminate();
			MRT_CORE_ASSERT(false);
		}
		
		//Create glfw context in the window
		glfwMakeContextCurrent(glfwwindow);
		glfwSetFramebufferSizeCallback(glfwwindow, [](GLFWwindow* window, int width, int height) { RenderCommands::SetViewport(0, 0, width, height); });
		
		//dis-able vsync
		glfwSwapInterval(0);
		//set the api
		RenderAPI::SetAPI(renderAPI);
		
		//imgui
		IMGUI_CHECKVERSION();
    	auto createContext = ImGui::CreateContext();
		MRT_CORE_ASSERT(createContext);
    	ImGuiIO& io = ImGui::GetIO(); (void)io;
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		MRT_PRINT("Window And Renderer Initialized..")

	}

	void Window::UpdateTitle()
	{
		Transform& CameraTransform = Scene::GetCameraCurrent()->Transform;

        //set window
        std::string total(std::string("MortarEngine v0.01 " + std::string(Application::Get().GetAppSpec().Title)));
		glfwSetWindowTitle(Application::GetWindow().GetNativeWindow(), total.c_str());
	}

	void Window::Push()
	{
		MRT_PROF();

		//swap the back buffer to the screen buffer
		glfwSwapBuffers(glfwwindow);
		glfwPollEvents();

	}

	void Window::Shutdown() {
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

}
