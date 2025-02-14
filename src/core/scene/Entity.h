#pragma once

#include "Utils.h"
#include "core/resource/Model.h"
#include "core/math/Transform.h"
#include "core/linking/MortarObject.h"

namespace MortarCore
{
    class Entity : public MortarObject
    {
        
        public:

            Entity(uint32_t id) : MortarObject(), Name("Entity") {}
            Entity(std::string name) : MortarObject(), Name(name){};
            Entity(const Entity&) = default;
            virtual ~Entity() = default;
            
            // Called after the object is instantiated
            virtual void Awake() {};

            // Called once per tick
            virtual void Tick() {}

            // Called every frame 
            virtual void Update(double delta) {}
            
            // Called after this object gets its model drawn, but hasn't been pushed to the screen yet
            virtual void Draw() {}

            // Called after this object gets destroyed, right before it is freed from memory
            virtual void Destroy() {}

            template <class T>
            inline bool IsType(){ return dynamic_cast<T*>(this) != nullptr; }

            template <class T>
            inline T* Get() { return dynamic_cast<T*>(this); }

            void RegisterProperties() override
            {
                Reflection::RegisterProperty(m_ID, "Name", VariantType::STRING, &Name);
                Reflection::RegisterProperty(m_ID, "IsActive", VariantType::BOOL, &IsActive);
            }

        public:
            std::string Name;
            bool IsActive = true;
            
            
    };
    
}