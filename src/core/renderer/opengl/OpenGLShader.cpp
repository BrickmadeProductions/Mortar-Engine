#include "OpenGLShader.h"

namespace MortarCore {

	OpenGLShader::OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath)
	{

		const char* vertSource = ReadFileContents(vertexFilePath).c_str();
		const char* fragSource = ReadFileContents(fragmentFilePath).c_str();
		//VERT

		MRT_CORE_ASSERT(glGetError());

		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

		MRT_CORE_ASSERT(glGetError());
		
		glShaderSource(vertexShader, 1, &vertSource, NULL);

		MRT_CORE_ASSERT(glGetError());

		glCompileShader(vertexShader);

		CompileErrors("VERTEX");
		MRT_CORE_ASSERT(glGetError());

		//FRAG
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		MRT_CORE_ASSERT(glGetError());

		glShaderSource(fragmentShader, 1, &fragSource, NULL);
		MRT_CORE_ASSERT(glGetError());

		glCompileShader(fragmentShader);
		CompileErrors("FRAGMENT");
		MRT_CORE_ASSERT(glGetError());

		m_ShaderID = glCreateProgram();
		MRT_CORE_ASSERT(glGetError());

		glAttachShader(m_ShaderID, vertexShader);
		MRT_CORE_ASSERT(glGetError());

		glAttachShader(m_ShaderID, fragmentShader);
		MRT_CORE_ASSERT(glGetError());

		glLinkProgram(m_ShaderID);
		glValidateProgram(m_ShaderID);
		MRT_CORE_ASSERT(glGetError());

		CompileErrors("PROGRAM");

		glDeleteShader(vertexShader);
		MRT_CORE_ASSERT(glGetError());

		glDeleteShader(fragmentShader);
		MRT_CORE_ASSERT(glGetError());
	}
	
	OpenGLShader::~OpenGLShader(){ glDeleteProgram(m_ShaderID); }

	void OpenGLShader::Activate() const
	{
		glUseProgram(m_ShaderID);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::DeActivate() const
	{
		glUseProgram(0);
		MRT_CORE_ASSERT(glGetError());
	}

	uint32_t OpenGLShader::GetUnformLocation(const char* location) const
	{
		GLuint loc = glGetUniformLocation(m_ShaderID, location);
		MRT_CORE_ASSERT(glGetError());
		return loc;
	}

	void OpenGLShader::SetFloat(float f, const char* location) const
	{
		glUniform1f(GetUnformLocation(location), f);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::SetInt(int32_t i, const char* location) const
	{
		glUniform1i(GetUnformLocation(location), i);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::SetBool(bool b, const char* location) const
	{
		float value = 0;

		if (b) {
			value = 1;
		}

		glUniform1f(GetUnformLocation(location), value);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::SetVec2(glm::vec2 v2, const char* location) const
	{
		glUniform2f(GetUnformLocation(location), v2.x, v2.y);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::SetVec3(glm::vec3 v3, const char* location) const
	{
		glUniform3f(GetUnformLocation(location), v3.x, v3.y, v3.z);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::SetVec4(glm::vec4 v4, const char* location) const
	{
		glUniform1i(GetUnformLocation(location), 0);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::SetMat4(glm::mat4x4 m4, const char* location) const
	{

		glUniformMatrix4fv(GetUnformLocation(location), 1, GL_FALSE, glm::value_ptr(m4));
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::BindAttrib(uint32_t attrib, const char* location) const
	{
		glBindAttribLocation(m_ShaderID, attrib, location);
		MRT_CORE_ASSERT(glGetError());
	}

	void OpenGLShader::CompileErrors(const char* type) const
	{
		
		GLint hasCompiled;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &hasCompiled);

			MRT_CORE_ASSERT(hasCompiled == GL_FALSE);

			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(m_ShaderID, 1024, NULL, infoLog);
			}
		}
		else
		{
			glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &hasCompiled);

			MRT_CORE_ASSERT(hasCompiled == GL_FALSE);

			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(m_ShaderID, 1024, NULL, infoLog);
			}
		}
	}
}