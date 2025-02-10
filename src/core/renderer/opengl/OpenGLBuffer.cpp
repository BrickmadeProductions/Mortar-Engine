#include "OpenGLBuffer.h"

namespace MortarCore {

	//VERTEX BUFFER

	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* verts, uint32_t size)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_DYNAMIC_DRAW);
		MRT_CORE_ASSERT(!glGetError());
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer() 
	{ 
		glDeleteBuffers(1, &m_BufferID);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLVertexBuffer::UpdateBuffer(const void* verts, uint32_t size) const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, verts);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLVertexBuffer::Bind() const
	{ 
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); 
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLVertexBuffer::Unbind() const
	{ 
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		MRT_CORE_ASSERT(!glGetError());
	}

	//INDEX BUFFER

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t size)
	{
		glGenBuffers(1, &m_BufferID);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
		MRT_CORE_ASSERT(!glGetError());

		//devide by 3 because triangle
		m_IndexCount = size;

	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		MRT_CORE_ASSERT(!glGetError());
	}
}