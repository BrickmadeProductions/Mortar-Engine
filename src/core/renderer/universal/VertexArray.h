#pragma once

#include "core/renderer/universal/Buffer.h"

namespace MortarCore {

	class VertexArray {

	public:

		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() const = 0;

		virtual void PushVertexBuffer(const Ref<VertexBuffer>& vertBuffer, uint32_t divisor) = 0;
		virtual void SetIndexBuffer( const Ref<IndexBuffer>& indexBuffer) = 0;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }
		const uint32_t GetInstanceCount() { return m_DrawInstances; }

		static Ref<VertexArray> Create(uint32_t drawInstances);

	protected:

		uint32_t m_BufferID;
		uint32_t m_VertexBufferIndex;

		//the amount of instances we are going to draw using this buffer
		uint32_t m_DrawInstances = 1;
		
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}