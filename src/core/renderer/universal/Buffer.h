#pragma once

#include "Utils.h"

namespace MortarCore {

	class VertexBuffer {

	public:

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<VertexBuffer>CreateBuffer(float* verts, uint32_t size);

	protected:

		uint32_t m_BufferID;
	};

	class IndexBuffer {

	public:

		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<IndexBuffer> CreateBuffer(uint32_t* indicies, uint32_t size);

	protected:

		uint32_t m_BufferID;
	};
}