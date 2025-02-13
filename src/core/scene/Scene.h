#pragma once

#include "Utils.h"
#include "RenderEntity.h"
#include "core/component/Camera.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/RenderCommands.h"
#include "core/renderer/universal/Shader.h"

namespace MortarCore {

	class Scene 
	{
	public:

		Scene() = default;
		Scene(const Scene& scene) = default;
		~Scene() = default;

		static Camera* GetCameraCurrent();

		//Instantiates a blank entity of type T
		template <class T>
		Ref<T> Instantiate(std::string name) 
		{
			if (m_EntitiesByName.contains(name)) 
			{
				MRT_PRINT_ERR("ENTITY WITH THIS NAME ALREADY EXISTS")
				return nullptr;
			}
			
			m_InstanceNonce++;
			
			Ref<T> entity = CreateRef<T>(name);

			//add to EntitiesList
			m_Entities.emplace(m_InstanceNonce, entity);
			m_EntitiesByName.emplace(entity->Name, entity);
			
			//Call the awake function
			entity->Awake();
			
			return entity;
		}


		template <typename T>
		Ref<T> GetEntity(uint32_t objectID) { return m_Entities[objectID]; }
		
		template <typename T>
		Ref<T> GetEntity(std::string name) { return m_EntitiesByName[name]; }
		
		template <typename T>
		Ref<T> GetEntity() 
		{ 
			for (const auto& entityPair : m_Entities) 
			{
				auto& entity = entityPair.second;

				auto derivedEntity = std::dynamic_pointer_cast<T>(entity);

				if (derivedEntity) return derivedEntity;
				
    		} 

			return nullptr;
		}

		template <typename T>
		Ref<T> GetEntity(const std::function<bool(const Ref<Entity>)>& testCondition) 
		{ 
			for (const auto& entityPair : m_Entities) 
			{
				auto& entity = entityPair.second;

				auto derivedEntity = std::dynamic_pointer_cast<T>(entity);

				if (derivedEntity && testCondition) return derivedEntity;

    		} 

			return nullptr;
		}

		//Gets called after the renderer and window have been intiailized
		void Awake() 
		{ 
			MRT_PROF();
			
			for (const auto& e : m_Entities) 
			{
				//get current camera by last active
				if (e.second->IsType<Camera>() && e.second->IsActive) m_MainCamera = e.second->Get<Camera>();
				if (e.second->IsType<RenderEntity3D>()) e.second->Get<RenderEntity3D>()->BuildRenderData();
			}
		}
		//Called every frame
		void Update(double delta) 
		{ 
			MRT_PROF();
			for (const auto& e : m_Entities) 
			{
				if (!e.second->IsActive) continue;
				e.second->Update(delta); 
				
			} 
		}
		//Called every tick
		void Tick() 
		{ 
			
			MRT_PROF();
			for (const auto& e : m_Entities) 
			{ 
				if (!e.second->IsActive) continue; 
				e.second->Tick(); 
			} 
		}
		//Called every time the scene is about to draw
		void Draw() 
		{ 
			
			MRT_PROF();
			//clear screen
			RenderCommands::Clear();

			//submit batches to renderer
			for (const auto& e : m_Entities) 
			{
				if (!e.second->IsActive) continue;
				//call its draw function
				e.second->Draw(); 
			}
		}
		
	private:

		Camera* m_MainCamera;

		std::unordered_map<uint32_t, Ref<Entity>> m_Entities;
		std::unordered_map<std::string, Ref<Entity>> m_EntitiesByName;

		uint32_t m_InstanceNonce = 0;
	};

}