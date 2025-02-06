#pragma once

#include "OpenGLRenderAPI.h"

namespace MortarCore
{
    OpenGLRenderAPI::OpenGLRenderAPI()
	{

	}
	OpenGLRenderAPI::~OpenGLRenderAPI() 
	{ 
		
	}

    int OpenGLRenderAPI::Init()
    {
        //Load OpenGL
		//intiailize glad
		MRT_CORE_ASSERT(gladLoadGL());

        glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);

		MRT_PRINT("OpenGL version: ");
        MRT_PRINT(glGetString(GL_VERSION));

        return 1;
    }

    void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        //Create a viewport with OPENGL
		glViewport(x, y, width, height);

    }
    void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }
    void OpenGLRenderAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t vertCount)
    {
        VertexArray->Bind();
        glDrawArrays(GL_LINES, 0, vertCount);
    } 
}