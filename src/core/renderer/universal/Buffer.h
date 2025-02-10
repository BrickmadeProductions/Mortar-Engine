#pragma once

#include "Utils.h"

namespace MortarCore {

	struct ShaderElement
	{	
	public:

		enum ShaderElementType
		{
			//bools are ints
			Float,
			Int,
			Bool,
			Vec2f,
			Vec3f,
			Vec4f,
			Vec2i,
			Vec3i,
			Vec4i,

		};

		ShaderElement(std::string name, ShaderElementType type) : Name(name), Type(type), Offset(0) { }
		
		
		uint32_t GetComponents()
		{
			switch (Type)
			{
				case ShaderElementType::Float: return 1;
				case ShaderElementType::Int: return 1; 
				case ShaderElementType::Bool: return 1; 
				case ShaderElementType::Vec2f: return 2;
				case ShaderElementType::Vec3f: return 3;
				case ShaderElementType::Vec4f: return 4;
				case ShaderElementType::Vec2i: return 2;
				case ShaderElementType::Vec3i: return 3;
				case ShaderElementType::Vec4i: return 4;
				default: MRT_CORE_ASSERT(false); return 0;
			}
	
		}
		uint32_t GetSize()
		{
			switch (Type)
			{
				case ShaderElementType::Float: return 1 * sizeof(float);
				case ShaderElementType::Int: return 1 * sizeof(int); 
				case ShaderElementType::Bool: return 1 * sizeof(bool); 
				case ShaderElementType::Vec2f: return 2 * sizeof(float);
				case ShaderElementType::Vec3f: return 3 * sizeof(float);
				case ShaderElementType::Vec4f: return 4 * sizeof(float);
				case ShaderElementType::Vec2i: return 2 * sizeof(int);
				case ShaderElementType::Vec3i: return 3 * sizeof(int);
				case ShaderElementType::Vec4i: return 4 * sizeof(int);
				default: MRT_CORE_ASSERT(false); return 0;
			}
	
		}
		
		std::string Name;
		ShaderElementType Type;
		size_t Offset;

	};

	struct BufferLayout
	{

		uint32_t Stride = 0;

		BufferLayout() = default;
		//initialize with layout specified
		BufferLayout(std::initializer_list<ShaderElement> elements)
			: m_Elements(elements)
		{
			SetOffsetAndStride();
		}

		void SetOffsetAndStride()
		{
			uint32_t offset = 0;
			Stride = 0;
			for (auto& e : m_Elements)
			{
				e.Offset = offset;
				Stride += e.GetSize();
				offset += e.GetSize();			
			}

		}
		std::vector<ShaderElement>& GetElements(){ return m_Elements; }

		private:
			
			std::vector<ShaderElement> m_Elements;
	};

	class VertexBuffer {

	public:

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void UpdateBuffer(const void* verts, uint32_t size) const = 0;

		static Ref<VertexBuffer>CreateBuffer(const void* verts, uint32_t size);
		
		void SetLayout(BufferLayout& layout) { m_BufferLayout = &layout; }
		BufferLayout& GetLayout() { return *m_BufferLayout; }

	protected:

		uint32_t m_BufferID;
		BufferLayout* m_BufferLayout;
	};

	class IndexBuffer {

	public:

		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<IndexBuffer> CreateBuffer(uint32_t* indicies, uint32_t size);

		uint32_t GetIndexCount() { return m_IndexCount; }

	protected:

		uint32_t m_BufferID;
		uint32_t m_IndexCount;
	};
}