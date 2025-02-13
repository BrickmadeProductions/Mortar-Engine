#pragma once

#include "core/renderer/universal/Shader.h"

namespace MortarCore {

	class OpenGLShader : public Shader {

	public:

		OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath);
		OpenGLShader(const char* computePath);
		virtual ~OpenGLShader();

		virtual void Activate() const override;
		virtual void DeActivate() const override;

		virtual void SetFloat(float f, const char* location) const override;
		virtual void SetInt(int32_t i, const char* location) const override;
		virtual void SetBool(bool b, const char* location) const override;
		virtual void SetVec2(glm::vec2 v2, const char* location) const override;
		virtual void SetVec3(glm::vec3 v3, const char* location) const override;
		virtual void SetVec4(glm::vec4 v4, const char* location) const override;
		virtual void SetMat4(glm::mat4x4 m4, const char* location) const override;

		virtual void LinkTexture(uint32_t textureID, uint32_t textureUnit, const char* location) const override;

		virtual void BindAttrib(uint32_t attrib, const char* location) const override;

	protected:
	
		virtual uint32_t GetUnformLocation(const char*) const override;
		virtual void CompileErrors(const char* type, uint32_t shaderID) const override;

	};
}