#include "VertexArray.h"

#include "core/renderer/RenderAPI.h"
#include "core/renderer/opengl/OpenGLVertexArray.h"

namespace MortarCore
{
	Ref<VertexArray> VertexArray::Create(const std::vector<Ref<VertexBuffer>>& vertBuffers, const Ref<IndexBuffer>& indexBuffer)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::OPENGL: return CreateRef<OpenGLVertexArray>(vertBuffers, indexBuffer);

			case RenderAPI::API::VULKAN: return nullptr;

			default: return nullptr;
		}
	}
}