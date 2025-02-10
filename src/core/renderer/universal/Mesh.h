#pragma once

#include "Utils.h"
#include "core/renderer/universal/Buffer.h"

namespace MortarCore {
    
struct Material;

class VertexArray;

	//MESH STRUCTURE
	struct Mesh
	{
	public:
	
		Mesh(Mesh&) = default;
		Mesh(std::vector<float> vertArray, std::vector<uint32_t> indices, BufferLayout bufferLayout) : m_VertexData(vertArray), m_Indices(indices), m_BufferLayout(bufferLayout) {}
		
		std::vector<float>& GetVertexData() { return m_VertexData; }
		std::vector<uint32_t>& GetIndiceData() { return m_Indices; }
		BufferLayout& GetBufferLayout() { return m_BufferLayout; }


		Ref<Material> m_Material;

	private:
		
		BufferLayout m_BufferLayout;

		std::vector<float> m_VertexData;
		std::vector<uint32_t> m_Indices;

	};


}
