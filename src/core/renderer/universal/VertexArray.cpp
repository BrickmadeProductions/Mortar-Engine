#include "VertexArray.h"

#include "core/renderer/RenderAPI.h"
#include "core/renderer/opengl/OpenGLVertexArray.h"

namespace MortarCore
{
	Ref<VertexArray> VertexArray::Create(uint32_t drawInstances)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::OPENGL: return CreateRef<OpenGLVertexArray>(drawInstances);

			case RenderAPI::API::VULKAN: return nullptr;

			default: return nullptr;
		}
	}
}