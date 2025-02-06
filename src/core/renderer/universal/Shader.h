#pragma once

#include "Utils.h"

namespace MortarCore {

	class Shader
	{
		
	public:

		static Ref<Shader> CreateProgram(const char* vertexFilePath, const char* fragmentFilePath);

		virtual ~Shader() = default;

		virtual void Activate() const = 0;
		virtual void DeActivate() const = 0;

		virtual void SetFloat(float f, const char* location) const = 0;
		virtual void SetInt(int32_t i, const char* location) const = 0;
		virtual void SetBool(bool b, const char* location) const = 0;
		virtual void SetVec2(glm::vec2 v2, const char* location) const = 0;
		virtual void SetVec3(glm::vec3 v3, const char* location) const = 0;
		virtual void SetVec4(glm::vec4 v4, const char* location) const = 0;
		virtual void SetMat4(glm::mat4x4 m4, const char* location) const = 0;

		virtual void BindAttrib(uint32_t attrib, const char* location) const = 0;

		virtual uint32_t GetShaderID() { return m_ShaderID; }

	protected:

		uint32_t m_ShaderID;

		virtual uint32_t GetUnformLocation(const char*) const = 0;

		virtual void CompileErrors(const char* type) const = 0;
		
		std::string ReadFileContents(const char* filename)
		{
			std::ifstream in(filename, std::ios::binary);
			if (in)
			{
				std::string contents;
				in.seekg(0, std::ios::end);
				contents.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&contents[0], contents.size());
				in.close();
				return(contents);
			}
			throw(errno);
		}


	};

}