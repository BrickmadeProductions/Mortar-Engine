#include "OpenGLBuffer.h"

namespace MortarCore {

	//VERTEX BUFFER

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verts, uint32_t size)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_DYNAMIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer() 
	{ 
		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLVertexBuffer::Bind() const
	{ 
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); 
	}

	void OpenGLVertexBuffer::Unbind() const
	{ 
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
	}

	//INDEX BUFFER

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t size) :
		m_Count(size)
	{
		glCreateBuffers(1, &m_BufferID);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 

		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}