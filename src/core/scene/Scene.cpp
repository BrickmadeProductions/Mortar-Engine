#include "Scene.h"
#include "core/Application.h"

namespace MortarCore 
{
    
    Camera* Scene::GetCameraCurrent() { return Application::GetScene().m_MainCamera; }


}