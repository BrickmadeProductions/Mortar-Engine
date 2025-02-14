#pragma once

#include "Utils.h"
#include "core/renderer/RenderAPI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"

namespace MortarCore
{
    class ImGUILayer
    {   
    public:

        virtual ~ImGUILayer() = default;

        static Scope<ImGUILayer> Initialize();

        void Draw();
        virtual void PreFrame() = 0;
        virtual void PostFrame() = 0;

    private:
        std::vector<float> m_FrameTimes;
    };
    
    
}