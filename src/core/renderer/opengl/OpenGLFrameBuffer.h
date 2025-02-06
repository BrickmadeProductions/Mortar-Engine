#pragma once

#include "core/renderer/universal/FrameBuffer.h"

namespace MortarCore 
{
    class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer();
		virtual ~OpenGLFrameBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	};

}