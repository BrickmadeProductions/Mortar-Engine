#pragma once

#include "Utils.h"
#include "core/vendor/imgui/ImGui.h"


namespace MortarCore
{
    class ImGUILayerOpenGL : public ImGUILayer
    {   
        public:

        ImGUILayerOpenGL();
        virtual ~ImGUILayerOpenGL();

        void PreFrame() override;
        void PostFrame() override;
    };

    
}