#include "OpenGLShader.h"

namespace MortarCore {

	OpenGLShader::OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath)
	{
		if (!vertexFilePath || !fragmentFilePath) MRT_CORE_ASSERT(false);

		std::string vertSourceStr = ReadFileContents(vertexFilePath);
		std::string fragSourceStr = ReadFileContents(fragmentFilePath);

		const char* vertSource = vertSourceStr.c_str();
		const char* fragSource = fragSourceStr.c_str();

		//VERT
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertSource, nullptr);
		glCompileShader(vertexShader);
		CompileErrors("VERTEX", vertexShader);
		MRT_CORE_ASSERT(!glGetError());
		
		//FRAG
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragSource, nullptr);
		glCompileShader(fragmentShader);
		CompileErrors("FRAGMENT", fragmentShader);
		MRT_CORE_ASSERT(!glGetError());

		m_ProgramID = glCreateProgram();

		glAttachShader(m_ProgramID, vertexShader);
		glAttachShader(m_ProgramID, fragmentShader);
		MRT_CORE_ASSERT(!glGetError());


		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);

		CompileErrors("PROGRAM", m_ProgramID);
		MRT_CORE_ASSERT(!glGetError());

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		MRT_CORE_ASSERT(!glGetError());
		MRT_PRINT_WARN("Vert + Frag Shader Program Successfully Created...")
		

	}

	OpenGLShader::OpenGLShader(const char* computeFilePath)
	{
		if (!computeFilePath) MRT_CORE_ASSERT(false);

		std::string computeSourcstr = ReadFileContents(computeFilePath);

		const char* computeSource = computeSourcstr.c_str();

		//COMPUTE
		GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(computeShader, 1, &computeSource, nullptr);
		glCompileShader(computeShader);
		CompileErrors("COMPUTE", computeShader);
		MRT_CORE_ASSERT(!glGetError());

		m_ProgramID = glCreateProgram();

		glAttachShader(m_ProgramID, computeShader);
		MRT_CORE_ASSERT(!glGetError());


		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);

		CompileErrors("PROGRAM", m_ProgramID);
		MRT_CORE_ASSERT(!glGetError());

		glDeleteShader(computeShader);

		MRT_CORE_ASSERT(!glGetError());
		MRT_PRINT_WARN("Compute Shader Program Successfully Created...")

	}
	
	
	OpenGLShader::~OpenGLShader()
	{ 
		glDeleteProgram(m_ProgramID); 
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::Activate() const
	{
		glUseProgram(m_ProgramID);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::DeActivate() const
	{
		glUseProgram(0);
		MRT_CORE_ASSERT(!glGetError());
	}

	uint32_t OpenGLShader::GetUnformLocation(const char* location) const
	{
		GLuint loc = glGetUniformLocation(m_ProgramID, location);
		MRT_CORE_ASSERT(!glGetError());
		return loc;
	}

	void OpenGLShader::SetFloat(float f, const char* location) const
	{
		glUniform1f(GetUnformLocation(location), f);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::SetInt(int32_t i, const char* location) const
	{
		glUniform1i(GetUnformLocation(location), i);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::SetBool(bool b, const char* location) const
	{
		float value = 0;
		if (b) value = 1;

		glUniform1f(GetUnformLocation(location), value);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::SetVec2(glm::vec2 v2, const char* location) const
	{
		glUniform2f(GetUnformLocation(location), v2.x, v2.y);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::SetVec3(glm::vec3 v3, const char* location) const
	{
		glUniform3f(GetUnformLocation(location), v3.x, v3.y, v3.z);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::SetVec4(glm::vec4 v4, const char* location) const
	{
		glUniform1i(GetUnformLocation(location), 0);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::SetMat4(glm::mat4x4 m4, const char* location) const
	{

		glUniformMatrix4fv(GetUnformLocation(location), 1, GL_FALSE, glm::value_ptr(m4));
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::LinkTexture(uint32_t textureID, uint32_t textureUnit, const char* location) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glUniform1i(GetUnformLocation(location), textureUnit);
		MRT_CORE_ASSERT(!glGetError())
	}

	void OpenGLShader::BindAttrib(uint32_t attrib, const char* location) const
	{
		glBindAttribLocation(m_ProgramID, attrib, location);
		MRT_CORE_ASSERT(!glGetError());
	}

	void OpenGLShader::CompileErrors(const char* type, uint32_t shaderID) const
	{
		char* infoLog;
		GLint infoLogLength;

		if (type != "PROGRAM")
		{
			GLint hasCompiled;

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &hasCompiled);

			if (hasCompiled == GL_FALSE)
			{
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
				infoLog = new char[infoLogLength];

				glGetShaderInfoLog(shaderID, infoLogLength, &infoLogLength, infoLog);

				MRT_PRINT_ERR(std::string(type) + " Shader Failed To Compile: " + std::string(infoLog));

			}
			MRT_CORE_ASSERT(hasCompiled);
		}
		else
		{
			GLint hasLinked, hasValidated;
			

			glGetProgramiv(shaderID, GL_LINK_STATUS, &hasLinked);
			glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &hasValidated);

			if (hasLinked == GL_FALSE)
			{
				
				glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

				infoLog = new char[infoLogLength];

				glGetProgramInfoLog(shaderID, infoLogLength, &infoLogLength, infoLog);

				MRT_PRINT_ERR("Shader PROGRAM Failed To Link: " + std::string(infoLog));
				
			}


			if (hasValidated == GL_FALSE)
			{
				
				glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

				infoLog = new char[infoLogLength];

				glGetProgramInfoLog(shaderID, infoLogLength, &infoLogLength, infoLog);

				MRT_PRINT_ERR("Shader PROGRAM Failed To Validate: " + std::string(infoLog));
				
			}
			MRT_CORE_ASSERT(hasLinked);
			MRT_CORE_ASSERT(hasValidated);
		}

		
	}
}