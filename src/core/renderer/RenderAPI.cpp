#include "RenderAPI.h"
#include "core/renderer/opengl/OpenGLRenderAPI.h"

namespace MortarCore
{
    
    //intiailize to opengl, we can change it in the initializer
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::OPENGL;
    uint32_t RenderAPI::s_CurrentTextureUnit = 0;

    Scope<RenderAPI> RenderAPI::Create()
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::OPENGL: return CreateScope<OpenGLRenderAPI>();
            case RenderAPI::API::VULKAN: return nullptr;

            default: return nullptr;
        }
    }

} 
