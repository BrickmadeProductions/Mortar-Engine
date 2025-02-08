#pragma once

#include "Utils.h"
#include "core/renderer/universal/Buffer.h"
#include "core/renderer/universal/VertexArray.h"

namespace MortarCore {

	class OpenGLVertexArray : public VertexArray {

	public:

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void PushVertexBuffer(const Ref<VertexBuffer>& vertBuffer);
		virtual void SetIndexBuffer( const Ref<IndexBuffer>& indexBuffer);
		virtual void Bind() override;
		virtual void Unbind() const override;
	};

}