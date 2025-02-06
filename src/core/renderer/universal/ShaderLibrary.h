#pragma once

#include "Shader.h"

namespace MortarCore
{

class Shader;

    class ShaderLibrary
	{
	public:

		Ref<Shader> GetShader(uint32_t shaderID) { return m_Shaders[shaderID]; }
		
		void CacheShader(Ref<Shader>& shader) { m_Shaders.emplace(shader.get()->GetShaderID(), shader); }

	private:
	
		eastl::unordered_map<uint32_t, Ref<Shader>> m_Shaders;
	};
} 

