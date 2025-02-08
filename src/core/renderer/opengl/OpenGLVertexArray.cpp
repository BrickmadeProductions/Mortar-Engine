#include "OpenGLVertexArray.h"

namespace MortarCore
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderElement::ShaderElementType type)
	{
		switch (type)
		{
			case ShaderElement::ShaderElementType::Int:    return GL_INT;
			case ShaderElement::ShaderElementType::Bool:    return GL_BOOL;
			case ShaderElement::ShaderElementType::Float:    return GL_FLOAT;
			case ShaderElement::ShaderElementType::Vec2f:   return GL_FLOAT;
			case ShaderElement::ShaderElementType::Vec3f:   return GL_FLOAT;
			case ShaderElement::ShaderElementType::Vec4f:   return GL_FLOAT;
			case ShaderElement::ShaderElementType::Vec2i:     return GL_INT;
			case ShaderElement::ShaderElementType::Vec3i:     return GL_INT;
			case ShaderElement::ShaderElementType::Vec4i:      return GL_INT;
			case ShaderElement::ShaderElementType::Mat3:     return GL_FLOAT;
			case ShaderElement::ShaderElementType::Mat4:     return GL_INT;
		}

		MRT_CORE_ASSERT(false);
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		m_VertexBufferIndex = 0;
		glGenVertexArrays(1, &m_BufferID);
		MRT_CORE_ASSERT(!glGetError());
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_BufferID);
	}

	void OpenGLVertexArray::PushVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		
		glBindVertexArray(m_BufferID);
		MRT_CORE_ASSERT(!glGetError());

		vertexBuffer->Bind();
		MRT_CORE_ASSERT(!glGetError());
		
		auto& layout = vertexBuffer->GetLayout();

		for (auto& element : layout.GetElements())
		{
			//MRT_PRINT("Vertex Attrib Index: " + std::to_string(m_VertexBufferIndex) + " Element Count: " + std::to_string(element.GetComponents()) + " Stride: " + std::to_string(layout.Stride));
			//MRT_PRINT(element.Offset);
			//default layout (abstract later)
			//(vertexPos, normalDir, texCoord)
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponents(), 
				ShaderDataTypeToOpenGLBaseType(element.Type),
				GL_FALSE,
				layout.Stride,
				(GLvoid*)(element.Offset));
			MRT_CORE_ASSERT(!glGetError());
	
			glEnableVertexAttribArray(m_VertexBufferIndex);
			MRT_CORE_ASSERT(!glGetError());
	
			m_VertexBufferIndex++;
		}

		//add to list
		m_VertexBuffers.push_back(vertexBuffer);
		
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& IndexBuffer)
	{
		glBindVertexArray(m_BufferID);
		MRT_CORE_ASSERT(!glGetError());

		IndexBuffer->Bind();

		m_IndexBuffer = IndexBuffer;
	}

	void OpenGLVertexArray::Bind()
	{

		
		glBindVertexArray(m_BufferID);
		MRT_CORE_ASSERT(!glGetError());
		
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
		MRT_CORE_ASSERT(!glGetError());
	}
}