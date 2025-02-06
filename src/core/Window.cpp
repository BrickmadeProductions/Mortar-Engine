#include "Window.h"
#include "core/renderer/RenderCommands.h"

namespace MortarCore {

	Window::Window(const char* t, RenderAPI::API renderAPI, const uint32_t w, const uint32_t h) : title(*t), windowWidth(w), windowHeight(h)
	{
		//Init GLFW
		MRT_CORE_ASSERT(glfwInit());

		//Tell GLFW versions
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
		//set the api
		RenderAPI::SetAPI(renderAPI);

		//initialze static renderAPI
		MRT_CORE_ASSERT(RenderCommands::InitializeAPI());

		RenderCommands::SetClearColor(glm::vec4(0.5f, 0.8f, 0.9f, 1.0f));
		
		MRT_PRINT("Window And Renderer Initialized..")

	}

	void Window::Push()
	{
		//swap the back buffer to the screen buffer
		glfwSwapBuffers(glfwwindow);
		glfwPollEvents();
	}

}
