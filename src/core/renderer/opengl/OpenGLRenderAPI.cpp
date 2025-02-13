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

    void GLAPIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        if (severity == GL_DEBUG_SEVERITY_HIGH && type == GL_DEBUG_TYPE_ERROR) { MRT_PRINT_ERR(message); }
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

        //LINES OR FILLED
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

        //ENABLE WHEN STABLE
        glEnable(GL_CULL_FACE);

        glFrontFace(GL_CCW);

		MRT_PRINT("OpenGL version: ");
        MRT_PRINT(glGetString(GL_VERSION));

        MRT_CORE_ASSERT(!glGetError());

        //debug
        // Ensure that OpenGL debug output is enabled
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);  // Synchronize with the callback

        // Register the debug callback function
        glDebugMessageCallback(OpenGLDebugCallback, nullptr);

        // Optional: You can specify the message severity you want to handle
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);  // Handle high severity messages

        return 1;
    }


    void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        //Create a viewport with OPENGL
		glViewport(x, y, width, height);
        MRT_CORE_ASSERT(!glGetError());

    }
    void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
        MRT_CORE_ASSERT(!glGetError());
    }
    void OpenGLRenderAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        MRT_CORE_ASSERT(!glGetError());
    }

    void OpenGLRenderAPI::DrawInstanced(const Ref<VertexArray>& VertexArray, uint32_t vertCount, uint32_t instanceCount) 
    {
        VertexArray->Bind();
        glDrawElementsInstanced(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, (void*)0, instanceCount);
        VertexArray->Unbind();
        MRT_CORE_ASSERT(!glGetError());
    }

    void OpenGLRenderAPI::LoadTexture(Ref<Texture>& tex)
    {
        s_CurrentTextureUnit++;

        // Step 2: Generate an OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        tex->SetTextureID(textureID);
        tex->SetTextureUnit(s_CurrentTextureUnit);

        // Step 3: Upload the image data to OpenGL
        GLenum format = GL_RGB; // Default format (for RGB images)
        if (tex->GetChannels() == 4)  format = GL_RGBA; // Use RGBA if the image has an alpha channel           

        // Upload image data to OpenGL (use the data with the correct format)
        glTexImage2D(GL_TEXTURE_2D, 0, format, tex->GetWidth(), tex->GetHeight(), 0, format, GL_UNSIGNED_BYTE, tex->GetData());

        // Step 4: Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Step 5: Generate mipmaps (optional, improves performance and visual quality)
        glGenerateMipmap(GL_TEXTURE_2D);
        
        // Step 6: Free image data after uploading it to the GPU
        ImageLoader::FreeImage(tex->GetData());
    }
}