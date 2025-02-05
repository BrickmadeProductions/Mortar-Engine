#include "Buffer.h"

namespace MortarCore
{
	VertexBuffer& VertexBuffer::CreateBuffer(float* verts, uint32_t size) 
	{
		switch (Application::Get().GetRenderer())
		{
			case Renderer::API::OPENGL: return &OpenGLVertexBuffer(verts, size);

			case Renderer::API::VULKAN: return nullptr;
		}
	}

	IndexBuffer& IndexBuffer::CreateBuffer(uint32_t* indicies, uint32_t size)
	{
		switch (Application::GetRenderer()->GetAPI())
		{
			case Renderer::API::OPENGL: return &OpenGLIndexBuffer(indicies, size);

			case Renderer::API::VULKAN: return nullptr;
		}
	}
}