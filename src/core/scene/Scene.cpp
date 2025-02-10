#include "Scene.h"
#include "core/Application.h"

namespace MortarCore 
{
    
    Camera* Scene::GetCameraCurrent()
    {
        Camera* camera = Application::GetScene().m_MainCamera;
        MRT_CORE_ASSERT(camera);
        return camera;
    }


}