#include "Utils.h"

namespace MortarCore {

	class Window
	{
	public:

		Window(const char* title, const uint32_t width, const uint32_t height);
		Window() = default;
		~Window() = default;

		GLFWwindow* GetWindow() { return glfwwindow; }
		uint32_t GetWidth() { return windowWidth; }
		uint32_t GetHeight() { return windowHeight; }

		void PushBuffer();

	private:

		char title;
		uint32_t windowWidth, windowHeight;
		GLFWwindow* glfwwindow;

	};
}