#pragma once

#include "Utils.h"
#include "core/renderer/universal/Buffer.h"
#include "Resource.h"

namespace MortarCore {
    
struct Material;

class VertexArray;

	//MESH STRUCTURE
	struct Mesh : public Resource
	{
	public:
	
		Mesh(std::vector<char> vertArray, std::vector<uint32_t> indices, BufferLayout bufferLayout) : m_VertexData(vertArray), m_Indices(indices), m_BufferLayout(bufferLayout) {}
		
		std::vector<char>& GetVertexData() { return m_VertexData; }
		std::vector<uint32_t>& GetIndiceData() { return m_Indices; }
		BufferLayout& GetBufferLayout() { return m_BufferLayout; }

		Ref<Material> m_Material;

	private:

		BufferLayout m_BufferLayout;

		std::vector<char> m_VertexData;
		std::vector<uint32_t> m_Indices;

	};


}
