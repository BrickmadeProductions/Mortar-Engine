#pragma once

#include "core/renderer/universal/Model.h"

namespace MortarCore
{
    class Entity
    {
        
        public:

            Entity() = default;
            Entity(const Entity&) = default;
            ~Entity() = default;
            
            //Called once per tick
            virtual void Tick() = 0;

            //Called every frame 
            virtual void Update() = 0;
            
            //Called after this object gets its model drawn, but hasn't been pushed to the screen yet
            virtual void Draw() = 0;

            void LoadModel(Ref<Model>& model) { m_Model = model; }
            Ref<Model> GetModel() { return m_Model; }

        private:
            
            Ref<Model> m_Model;

    };
    
}