#include "Utils.h"
#include "renderer/RenderAPI.h"
#include "renderer/universal/FrameBuffer.h"

namespace MortarCore {

	class Window
	{
	public:

		Window(const char* title, RenderAPI::API renderAPI, const uint32_t width, const uint32_t height);
		~Window() = default;

		GLFWwindow* GetNativeWindow() { return glfwwindow; }

		uint32_t GetWidth() { return windowWidth; }
		uint32_t GetHeight() { return windowHeight; }

		void Push();

	private:

		char title;
		uint32_t windowWidth, windowHeight;
		GLFWwindow* glfwwindow;
	};
}