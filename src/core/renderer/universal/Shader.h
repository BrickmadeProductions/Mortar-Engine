#pragma once

#include "Utils.h"
#include "core/resource/Resource.h"
#include "core/renderer/universal/Buffer.h"

namespace MortarCore {

	class Shader : public Resource
	{
		
	public:

		static Ref<Shader> CreateProgram(const char* vertexFilePath, const char* fragmentFilePath);
		static Ref<Shader> CreateProgram(const char* compFilePath);

		virtual void Activate() const = 0;
		virtual void DeActivate() const = 0;

		virtual void SetFloat(float f, const char* location) const = 0;
		virtual void SetInt(int32_t i, const char* location) const = 0;
		virtual void SetBool(bool b, const char* location) const = 0;
		virtual void SetVec2(glm::vec2 v2, const char* location) const = 0;
		virtual void SetVec3(glm::vec3 v3, const char* location) const = 0;
		virtual void SetVec4(glm::vec4 v4, const char* location) const = 0;
		virtual void SetMat4(glm::mat4x4 m4, const char* location) const = 0;

		virtual void LinkTexture(uint32_t textureID, uint32_t textureUnit, const char* location) const = 0;

		virtual void BindAttrib(uint32_t attrib, const char* location) const = 0;

		virtual uint32_t GetShaderID() { return m_ProgramID; }
		
	protected:

		uint32_t m_ProgramID;


		virtual uint32_t GetUnformLocation(const char*) const = 0;

		virtual void CompileErrors(const char* type, uint32_t shaderID) const = 0;
		
		std::string ReadFileContents(const char* file)
		{
			std::ifstream in(file);
			
			MRT_CORE_ASSERT(in.is_open());
			
			std::stringstream buffer;

			if (in.is_open())
			{
				buffer << in.rdbuf();
				return buffer.str();
				
			}
			return "INVALID";
			
			
		}


	};

}