#pragma once

#include "ImGuiOpenGL.h"
#include "imgui_impl_opengl3.h"
#include "core/Application.h"

namespace MortarCore
{
    ImGUILayerOpenGL::ImGUILayerOpenGL()
    {
        ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow().GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init();

    }

    ImGUILayerOpenGL::~ImGUILayerOpenGL()
    {
        ImGui_ImplOpenGL3_Shutdown();
    }

    void ImGUILayerOpenGL::PreFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
    }

    void ImGUILayerOpenGL::PostFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui::UpdatePlatformWindows();
    }
    
}