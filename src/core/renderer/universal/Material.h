#pragma once

namespace MortarCore 
{
class Shader;

//MATERIAL STRUCTURE
	struct Material
	{
		Material() = default;
		Material(Material&) = default;
		Material(Ref<Shader>& shader) : m_Shader(shader) {}

		Ref<Shader> m_Shader;
	};
}