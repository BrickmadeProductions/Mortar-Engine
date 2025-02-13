#pragma once

#include "core/renderer/universal/Buffer.h"

namespace MortarCore {

	class VertexArray {

	public:

		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() const = 0;

		virtual void PushVertexBuffer(const Ref<VertexBuffer>& vertBuffer, uint32_t divisor) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual void SetShaderStorageBuffer(const Ref<ShaderStorageBuffer>& shaderStorageBufer) = 0;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }
		
		const Ref<ShaderStorageBuffer>& GetShaderStorageBuffer() { return m_ShaderStorageBuffer; }

		static Ref<VertexArray> Create();

	protected:

		uint32_t m_BufferID;
		uint32_t m_VertexAttribIndexIndex;

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

		Ref<ShaderStorageBuffer> m_ShaderStorageBuffer;

	};

}