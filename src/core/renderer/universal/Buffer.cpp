#include "Buffer.h"
#include "core/renderer/RenderAPI.h"
#include "core/renderer/opengl/OpenGLBuffer.h"

namespace MortarCore
{
	Ref<VertexBuffer> VertexBuffer::CreateBuffer(const void* verts, uint32_t size) 
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::OPENGL: return CreateRef<OpenGLVertexBuffer>(verts, size);

			case RenderAPI::API::VULKAN: return nullptr;

			default: return nullptr;
		}
	}

	Ref<IndexBuffer> IndexBuffer::CreateBuffer(uint32_t* indicies, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::OPENGL: return CreateRef<OpenGLIndexBuffer>(indicies, size);

			case RenderAPI::API::VULKAN: return nullptr;

			default: return nullptr;
		}
	}
}