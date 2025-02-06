#pragma once

#include "Utils.h"
#include "core/renderer/universal/Buffer.h"
#include "core/renderer/universal/VertexArray.h"

namespace MortarCore {

	class OpenGLVertexArray : public VertexArray {

	public:

		OpenGLVertexArray(const std::vector<Ref<VertexBuffer>>& vertBuffer, const Ref<IndexBuffer>& indexBuffer);
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	};

}