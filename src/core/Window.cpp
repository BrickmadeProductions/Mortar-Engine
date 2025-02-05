#include "Window.h"

namespace MortarCore {

	Window::Window(const char* t, const uint32_t w, const uint32_t h) : title(*t), windowWidth(w), windowHeight(h)
	{
		//Init GLFW
		if (!glfwInit()) return;

		//Tell GLFW versions
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		glfwwindow = glfwCreateWindow(windowWidth, windowHeight, t, NULL, NULL);

		//Check for errors
		if (glfwwindow == NULL) {

			std::cout << "Failed to create window!" << std::endl;
			glfwTerminate();
		}

		//ABSTRACT LATER FOR VULKAN
		//TODO

		//Create glfw context in the window
		glfwMakeContextCurrent(glfwwindow);

		//Load OpenGL
		gladLoadGL();

		//Create a viewport with OPENGL
		glViewport(0, 0, windowWidth, windowHeight);

		//glfwSetKeyCallback(glfwwindow, key_callback);
		std::cout << "\n" << std::endl;
		printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	}

	void Window::PushBuffer()
	{
		//swap the back buffer to the screen buffer
		glfwSwapBuffers(glfwwindow);
		glfwPollEvents();
	}

}
