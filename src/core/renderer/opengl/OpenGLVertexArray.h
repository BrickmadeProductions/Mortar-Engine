#pragma once

#include "Utils.h"
#include "core/renderer/universal/Buffer.h"
#include "core/renderer/universal/VertexArray.h"

namespace MortarCore {

	class OpenGLVertexArray : public VertexArray {

	public:

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void PushVertexBuffer(const Ref<VertexBuffer>& vertBuffer, uint32_t divisor) override;
		virtual void SetIndexBuffer( const Ref<IndexBuffer>& indexBuffer) override;

		virtual void SetShaderStorageBuffer(const Ref<ShaderStorageBuffer>& shaderStorageBufer) override;

		virtual void Bind() override;
		virtual void Unbind() const override;
	};

}