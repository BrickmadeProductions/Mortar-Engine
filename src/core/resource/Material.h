#pragma once

#include "Resource.h"

namespace MortarCore 
{
class Shader;
class Texture;

//MATERIAL STRUCTURE
	struct Material : public Resource
	{
		Material(Ref<Shader>& shader) : m_Shader(shader) {}

		Ref<Shader> m_Shader;
		Ref<Texture> m_MainTex;
	};
}