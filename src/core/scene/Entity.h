#pragma once

#include "Utils.h"
#include "core/renderer/universal/Model.h"
#include "core/math/Transform.h"

namespace MortarCore
{
    class Entity
    {
        
        public:

            Entity() : Name("Entity") {}
            Entity(std::string name) : Name(name){};
            Entity(const Entity&) = default;
            virtual ~Entity() = default;
            
            //Called after the object is instantiated
            virtual void Awake() {};

            //Called once per tick
            virtual void Tick() {}

            //Called every frame 
            virtual void Update(double delta) {}
            
            //Called after this object gets its model drawn, but hasn't been pushed to the screen yet
            virtual void PostDraw() {}

            template <class T>
            inline bool IsEntityOfType()
            {
                return dynamic_cast<T*>(this) != nullptr;
            }
            template <class T>
            inline T* Get()
            {
                return dynamic_cast<T*>(this);
            }

        public:
            std::string Name;
            bool IsActive = true;
            
            
    };
    
}