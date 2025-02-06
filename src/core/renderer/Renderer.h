#pragma once

#include "core/math/Math.h"
#include "core/component/Camera.h"
#include "core/renderer/RenderAPI.h"
#include "core/renderer/universal/Model.h"
#include "core/renderer/universal/Mesh.h"
#include "core/renderer/universal/Shader.h"
#include "core/renderer/ShaderLibrary.h"


namespace MortarCore
{
    class Renderer
    {        
    public:


    public:
    
        static void Submit(const Ref<Shader>& shader, const Ref<Model>& model, const Ref<Transform>& transform);
		
        static Camera& GetCamera() { return *s_CurrentCamera; }

        private:
        
            static Camera* s_CurrentCamera;
    };
   

}