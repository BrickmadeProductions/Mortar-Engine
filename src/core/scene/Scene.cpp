#include "Scene.h"
#include "core/Application.h"

namespace MortarCore 
{
    

    Camera* Scene::GetCameraCurrent()
    {
        Camera* camera = Application::Get().GetScene().GetEntity<Camera>([](const auto& camera) { return camera->IsActive; }).get();
        MRT_CORE_ASSERT(camera);
        return camera;
    }


}