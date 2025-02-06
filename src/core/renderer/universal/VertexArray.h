#pragma once

#include "core/renderer/universal/Buffer.h"

namespace MortarCore {

	class VertexArray {

	public:

		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const eastl::vector<Ref<VertexBuffer>>& GetVertexBuffers() { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }

		static Ref<VertexArray> Create(const std::vector<Ref<VertexBuffer>>& vertBuffers , const Ref<IndexBuffer>& indexBuffer);

	protected:

		uint32_t m_BufferID;
		uint32_t m_VertexBufferIndex = 0;
		
		eastl::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}