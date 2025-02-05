#pragma once

#include "Utils.h"
#include "core/Application.h"

namespace MortarCore {

	class VertexBuffer {

	public:

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetLength() const { return m_Count; }

		static VertexBuffer& CreateBuffer(float* verts, uint32_t size);

	protected:

		uint32_t m_Count;
		uint32_t m_BufferID;
	};

	class IndexBuffer {

	public:

		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetLength() const { return m_Count; }

		static IndexBuffer& CreateBuffer(uint32_t* indicies, uint32_t size);

	protected:

		uint32_t m_Count;
		uint32_t m_BufferID;
	};
}