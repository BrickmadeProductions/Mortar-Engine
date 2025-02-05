#include "OpenGLShader.h"

namespace MortarCore {

	OpenGLShader::OpenGLShader(const char* vertexFilePath, const char* fragmentFilePath)
	{
		//VERT
		OPEN_GL_DEBUG(printf("Start Shader Creation: %i\n", glGetError()));

		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		OPEN_GL_DEBUG(printf("Create Vertex Shader: %i\n", glGetError()));

		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		OPEN_GL_DEBUG(printf("Vertex Shader Source: %i\n", glGetError()));

		glCompileShader(vertexShader);
		compileErrors(vertexShader, "VERTEX");
		OPEN_GL_DEBUG(printf("Vertex Shader Compiled: %i\n", glGetError()));

		//FRAG
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		OPEN_GL_DEBUG(printf("Create Fragment Shader: %i\n", glGetError()));

		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		OPEN_GL_DEBUG(printf("Fragment Shader Source: %i\n", glGetError()));

		glCompileShader(fragmentShader);
		compileErrors(fragmentShader, "FRAGMENT");
		OPEN_GL_DEBUG(printf("Fragment Shader Compiled: %i\n", glGetError()));

		m_ShaderID = glCreateProgram();
		OPEN_GL_DEBUG(printf("GL Shader Program Created: %i\n", glGetError()));

		glAttachShader(m_ShaderID, vertexShader);
		OPEN_GL_DEBUG(printf("Vertex Shader Attached: %i\n", glGetError()));

		glAttachShader(m_ShaderID, fragmentShader);
		OPEN_GL_DEBUG(printf("Fragment Shader Attached: %i\n", glGetError()));

		glLinkProgram(m_ShaderID);
		glValidateProgram(m_ShaderID);
		OPEN_GL_DEBUG(printf("Shader Program Linked: %i\n", glGetError()));

		compileErrors(m_ShaderID, "PROGRAM");

		glDeleteShader(vertexShader);
		OPEN_GL_DEBUG(printf("Vertex Shader Object Deleted: %i\n", glGetError()));

		glDeleteShader(fragmentShader);
		OPEN_GL_DEBUG(printf("Fragment Shader Object Deleted: %i\n", glGetError()));
	}
	
	OpenGLShader::~OpenGLShader(){ glDeleteProgram(m_ShaderID); }

	void OpenGLShader::Activate() const
	{
		glUseProgram(m_ShaderID);
		OPEN_GL_DEBUG(printf("Activate Shader: %i\n", glGetError()));
	}

	void OpenGLShader::DeActivate() const
	{
		glUseProgram(0);
		OPEN_GL_DEBUG(printf("Deactivate Shader: %i\n", glGetError()));
	}

	uint32_t OpenGLShader::GetUnformLocation(const char* location) const
	{
		GLuint loc = glGetUniformLocation(m_ShaderID, location);
		OPEN_GL_DEBUG(printf("Get Uniform In Shader: %i\n", glGetError()));
		return loc;
	}

	void OpenGLShader::SetFloat(float f, const char* location) const
	{
		glUniform1f(GetUnformLocation(location), f);
		OPEN_GL_DEBUG(printf("Load Float To Shader: %i\n", glGetError()));
	}

	void OpenGLShader::SetInt(int32_t i, const char* location) const
	{
		glUniform1i(GetUnformLocation(location), i);
		OPEN_GL_DEBUG(printf("Load Int To Shader: %i\n", glGetError()));
	}

	void OpenGLShader::SetBool(bool b, const char* location) const
	{
		float value = 0;

		if (b) {
			value = 1;
		}

		glUniform1f(GetUnformLocation(location), value);
		OPEN_GL_DEBUG(printf("Load Bool To Shader: %i\n", glGetError()));
	}

	void OpenGLShader::SetVec2(glm::vec2 v2, const char* location) const
	{
		glUniform2f(GetUnformLocation(location), v2.x, v2.y);
		OPEN_GL_DEBUG(printf("Load Vector2 To Shader: %i\n", glGetError()));
	}

	void OpenGLShader::SetVec3(glm::vec3 v3, const char* location) const
	{
		glUniform3f(GetUnformLocation(location), v3.x, v3.y, v3.z);
		OPEN_GL_DEBUG(printf("Load Vector3 To Shader: %i\n", glGetError()));
	}

	void OpenGLShader::SetVec4(glm::vec4 v4, const char* location) const
	{
		glUniform1i(GetUnformLocation(location), 0);
		OPEN_GL_DEBUG(printf("Load Vector4 To Shader: %i\n", glGetError()));
	}

	void OpenGLShader::SetMat4(glm::mat4x4 m4, const char* location) const
	{

		glUniformMatrix4fv(GetUnformLocation(location), 1, GL_FALSE, glm::value_ptr(m4));
		OPEN_GL_DEBUG(printf("Load Matrix4x4 To Shader: %i\n", glGetError()));
	}

	void OpenGLShader::BindAttrib(uint32_t attrib, const char* location) const
	{
		glBindAttribLocation(m_ShaderID, attrib, location);
		OPEN_GL_DEBUG(printf("Bind Attribute to Shader: %i\n", glGetError()));
	}

	void OpenGLShader::CompileErrors(const char* type) const
	{
		
		GLint hasCompiled;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &hasCompiled);
			OPEN_GL_DEBUG(printf("Shader Compiled: %i\n", glGetError()));
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(m_ShaderID, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for " << type << "\n" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &hasCompiled);
			OPEN_GL_DEBUG(printf("Shader Linked: %i\n", glGetError()));
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(m_ShaderID, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for " << type << "\n" << std::endl;
			}
		}
	}
}