#pragma once

#include "Utils.h"
#include "core/renderer/universal/Model.h"
#include "core/math/Transform.h"

namespace MortarCore
{
    class Entity
    {
        
        public:

            Entity(std::string name) : Name(name), Transform() {};
            Entity(std::string name, Transform& t) : Name(name), Transform(t) {};
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

            void LoadModel(const Ref<Model>& model) { m_Model = model; }
            Ref<Model> GetModel() { return m_Model; }
        
            std::string Name;
            Transform Transform;
            bool IsActive = true;
            
        private:
            
            Ref<Model> m_Model;
            
    };
    
}