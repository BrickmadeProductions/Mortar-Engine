#include "Shader.h"


namespace MortarCore {

	Shader::CreateProgram(const char* vertexFile, const char* fragmentFile)
	{
		const char* vertexSource = ReadFileContents(vertexFile).c_str();
		const char* fragmentSource = ReadFileContents(fragmentFile).c_str();

		switch (Application::GetRenderer().)
		{
			case Renderer::API::OPENGL: return &OpenGLShader(vertexFile, fragmentFile);

			case Renderer::API::VULKAN: return nullptr;
		} 
	}

}