#include "core/Application.h"
#include "core/renderer/opengl/OpenGLFrameBuffer.h"

namespace MortarCore
{
	Ref<FrameBuffer> FrameBuffer::CreateBuffer()
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::OPENGL: return CreateRef<OpenGLFrameBuffer>();

			case RenderAPI::API::VULKAN: return nullptr;

			default: return nullptr;
		}
	}

}