#include "OpenGLVertexArray.h"

namespace MortarCore
{
	OpenGLVertexArray::OpenGLVertexArray(const std::vector<Ref<VertexBuffer>>& vertBuffer, const Ref<IndexBuffer>& indexBuffer)
	{

	}

	OpenGLVertexArray::~OpenGLVertexArray(){

	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_BufferID);

		//do all the bindings for the vertex buffers
		for (const auto& vertexBuffer : m_VertexBuffers)
		{
			
		}
	}

	void OpenGLVertexArray::Unbind() const
	{

	}
}