#pragma once
#include "core/renderer/universal/Buffer.h"

namespace MortarCore {

	class OpenGLVertexBuffer : public VertexBuffer 
	{

	public:
		OpenGLVertexBuffer(const void* verts, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void UpdateBuffer(const void* verts, uint32_t size) const override;
	};

	class OpenGLIndexBuffer : public IndexBuffer 
	{

	public:
		OpenGLIndexBuffer(uint32_t* indecies, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	};
	class OpenGLShaderStorageBuffer : public ShaderStorageBuffer 
	{

	public:
		OpenGLShaderStorageBuffer(const void* data, uint32_t size);
		virtual ~OpenGLShaderStorageBuffer();
		
		virtual void Bind() const override;
		virtual void Dispatch(uint32_t computeThreads) const override;

	};
}