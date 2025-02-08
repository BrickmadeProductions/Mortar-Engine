#pragma once

#include "Utils.h"
#include "core/scene/Entity.h"
#include "core/renderer/universal/Material.h"

namespace MortarCore
{

    class Renderer
    {        
    public:

        static void Submit(const Ref<Entity> entity);
    };
   

}