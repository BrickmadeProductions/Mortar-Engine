#include "OpenGLFrameBuffer.h"

namespace MortarCore 
{
    OpenGLFrameBuffer::OpenGLFrameBuffer()
	{
        glGenBuffers(1, &m_BufferID);
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer() 
	{ 
		glDeleteFramebuffers(1, &m_BufferID);
	}

	void OpenGLFrameBuffer::Bind() const
	{ 
		glBindFramebuffer(GL_ARRAY_BUFFER, m_BufferID); 
	}

	void OpenGLFrameBuffer::Unbind() const
	{ 
		glBindFramebuffer(GL_ARRAY_BUFFER, 0); 
	}

}