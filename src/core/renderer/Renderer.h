#pragma once

#include "Utils.h"
#include "core/scene/RenderEntity.h"
#include "core/renderer/universal/VertexArray.h"
#include "core/resource/Material.h"

namespace MortarCore
{
    class Renderer
    {        
    public:

		
        static void Submit(Ref<VertexArray>& vertexArray, Ref<Shader>& shader, uint32_t instanceCount);
        
    };
   

}