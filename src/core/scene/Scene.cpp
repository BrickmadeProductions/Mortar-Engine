#include "Scene.h"
#include "core/Application.h"

namespace MortarCore 
{
    
    Camera* Scene::GetCameraCurrent() { return Application::GetScene().m_MainCamera; }
    std::unordered_map<std::string, Ref<Entity>>& Scene::GetSceneEntities() { return Application::GetScene().m_SceneEntities; }

}