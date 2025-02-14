#pragma once

#include "ImGui.h"
#include "core/vendor/imgui/opengl/ImGuiOpenGL.h"
#include "core/Application.h"

namespace MortarCore
{

    Scope<ImGUILayer> ImGUILayer::Initialize()
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::OPENGL: return CreateScope<ImGUILayerOpenGL>();
            case RenderAPI::API::VULKAN: return nullptr;

            default: return nullptr;
        }
    }

    void ImGUILayer::Draw()
    {
        ImGui::Begin("Debug Info");

        ImGui::Text((std::to_string(Application::GetFPS()) + " FPS ").data());
		ImGui::Text((std::to_string(Application::GetFrameTime()) + " Ms ").data());

        //////////////////////
        // Grab frame samples
        //////////////////////

        if (m_FrameTimes.size() >= 100) 
        {
            m_FrameTimes.erase(m_FrameTimes.begin());
        }
        m_FrameTimes.push_back((float)Application::GetFPS());

        ImGui::PlotLines("Frame Time", [](void* data, int idx) -> float 
        { 
            std::vector<float>* frameTimes = static_cast<std::vector<float>*>(data);
            return frameTimes->at(idx); 

        }, &m_FrameTimes, uint32_t(m_FrameTimes.size()), 0, nullptr, 0.0f, 360.0f, ImVec2(250, 50));
       
        /////////////////////
        // Debug Camera Info
        ////////////////////

		Transform& CameraTransform = Scene::GetCameraCurrent()->Transform;
		ImGui::Text(("Camera Location: " + std::to_string(CameraTransform.position.x) + ", " + std::to_string(CameraTransform.position.y) + ", " + std::to_string(CameraTransform.position.z)).data());
		ImGui::Text(("Camera Rotation: " + std::to_string(CameraTransform.rotation.x) + ", " + std::to_string(CameraTransform.rotation.y) + ", " + std::to_string(CameraTransform.rotation.z)).data());
		ImGui::End();

        //////////////////////////
        // World Object Parameters
        //////////////////////////
        
        ImGui::Begin("World Settings");
        for (auto& e : Application::GetScene().GetSceneEntities())
        {
            ImGui::SeparatorText(e.second->Name.data());
            for (auto& p : Reflection::GetClassMeta(e.second->GetID()).m_Properties)
            {
                ImGui::PushID(int(e.second->GetID()));

                switch (p.second.GetType())
                {
                    case VariantType::INT: 
                        ImGui::DragInt(p.second.GetName().data(), p.second.GetValue<int>());
                        break;
                    case VariantType::BOOL: 
                        ImGui::Checkbox(p.second.GetName().data(), p.second.GetValue<bool>());
                        break;
                    case VariantType::FLOAT: 
                        ImGui::DragFloat(p.second.GetName().data(), p.second.GetValue<float>());
                        break;
                    case VariantType::DOUBLE: 
                        ImGui::DragFloat(p.second.GetName().data(), p.second.GetValue<float>());
                        break;
                    case VariantType::VEC2: 
                        ImGui::DragFloat2(p.second.GetName().data(), glm::value_ptr(*p.second.GetValue<glm::vec2>()));
                        break;
                    case VariantType::VEC3:
                        ImGui::DragFloat3(p.second.GetName().data(), glm::value_ptr(*p.second.GetValue<glm::vec3>()));
                        break;
                    case VariantType::VEC4: 
                        ImGui::DragFloat3(p.second.GetName().data(), glm::value_ptr(*p.second.GetValue<glm::vec4>()));
                        break;
                    case VariantType::OBJECT: 
                        if (p.first == "Transform")
                        {
                            Transform& transform = *p.second.GetValue<Transform>();
                            ImGui::DragFloat3("Position", glm::value_ptr(transform.position));
                            ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation));
                            ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale));
                            
                        }
                        break;
                    default: continue;
                    
                }
                ImGui::PopID();
            }
           
        }
        
        ImGui::End();

    }
    
}