#include "Buffer.h"

namespace MortarCore
{
	FrameBuffer& FrameBuffer::CreateBuffer()
	{
		switch (Application::GetRenderer().GetAPI())
		{
			case Renderer::API::OPENGL: return &OpenGLFrameBuffer( );

			case Renderer::API::VULKAN: return nullptr;
		}
	}

}