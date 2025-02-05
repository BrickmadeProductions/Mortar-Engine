#pragma once

#include "Utils.h"
#include "core/component/Camera.h"
#include "core/math/Transform.h"

#include "Shader.h"
#include "RenderObject.h"

namespace MortarCore 
{
	class Renderer 
	{
	public:

		enum API
		{
			OPENGL,
			VULKAN
		};

		Renderer(const API apiCurrent) : m_API(apiCurrent) {};
		~Renderer() = default;

		int Init();

		void Shutdown();

		void SubmitMesh(const Shader& shader, const Model& model, const Transform& transform);

		API GetAPI() const { return m_API; }

		Ref<Shader> GetShader(uint32_t shaderID) { return m_shaderLibrary[shaderID]; }
		void CacheShader(Ref<Shader> shader) { m_shaderLibrary.insert_or_assign(shader.get()->GetShaderID(), shader); }
		

	private:

		eastl::map<uint32_t, Ref<Shader>> m_shaderLibrary;

		API m_API;
	};
	

}