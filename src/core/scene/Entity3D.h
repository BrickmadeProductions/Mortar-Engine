#pragma once

#include "Utils.h"
#include "Entity.h"
#include "core/math/Transform.h"

namespace MortarCore
{
    class Entity3D : public Entity
    {
        
        public:
        
            Entity3D() : Entity("Entity3D"), Transform() {}
            Entity3D(std::string Name) : Entity(Name), Transform() {}
            Entity3D(std::string Name, Transform& transform) : Entity(Name), Transform(transform) {}
            virtual ~Entity3D() = default;

        public:

            Transform Transform;            
            
    };
    
}