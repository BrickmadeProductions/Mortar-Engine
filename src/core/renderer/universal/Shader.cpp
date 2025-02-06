#include "core/renderer/opengl/OpenGLShader.h"
#include "Shader.h"
#include "core/renderer/RenderAPI.h"

namespace MortarCore {

	Ref<Shader> Shader::CreateProgram(const char* vertexFile, const char* fragmentFile)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::OPENGL: return CreateRef<OpenGLShader>(vertexFile, fragmentFile);

			case RenderAPI::API::VULKAN: return nullptr;

			default: return nullptr;
		} 
	}

}