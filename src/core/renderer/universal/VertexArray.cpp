#include "VertexArray.h"

#include "core/renderer/RenderAPI.h"
#include "core/renderer/opengl/OpenGLVertexArray.h"

namespace MortarCore
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::OPENGL: return CreateRef<OpenGLVertexArray>();

			case RenderAPI::API::VULKAN: return nullptr;

			default: return nullptr;
		}
	}
}