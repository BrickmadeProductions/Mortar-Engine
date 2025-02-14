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
		static std::unordered_map<std::string, Ref<Entity>>& GetSceneEntities();

		// Instantiates a blank entity of type T
		template <class T>
		Ref<T> Instantiate(std::string name)
		{
			if (m_SceneEntities.contains(name)) 
			{
				MRT_PRINT_ERR("ENTITY WITH THIS NAME ALREADY EXISTS")
				return nullptr;
			}
			
			Ref<T> entity = MortarObject::Create<T>(name);

			m_SceneEntities.emplace(entity->Name, entity); // Add to local scene entities list
	
			entity->Awake(); //Call the awake function
			
			return entity;
		}
		
		// Destroys and frees the entity from memory
		void Destroy(uint64_t entityID)
		{
			m_SceneEntities.erase(Reflection::GetMortarObject<Entity>(entityID)->Name);
			
			Reflection::GetMortarObject<Entity>(entityID)->Destroy(); // Run destroy callback
        	Reflection::FreeMortarObject(entityID);
		}

		template <typename T>
		Ref<T> GetEntity(uint32_t objectID) { return Reflection::m_Entities[objectID]; }
		
		template <typename T>
		Ref<T> GetEntity(std::string name) { return m_SceneEntities[name]; }
		
		template <typename T>
		Ref<T> GetEntity() 
		{ 
			for (const auto& entityPair : m_SceneEntities) 
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
			for (const auto& entityPair : m_SceneEntities) 
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
			
			for (const auto& e : m_SceneEntities) 
			{
				//get current camera by last active
				if (e.second->IsType<Camera>() && e.second->IsActive) m_MainCamera = e.second->Get<Camera>();
				if (e.second->IsType<RenderEntity3D>()) e.second->Get<RenderEntity3D>()->Build();
			}
		}
		//Called every frame
		void Update(double delta) 
		{ 
			MRT_PROF();
			for (const auto& e : m_SceneEntities) 
			{
				if (!e.second->IsActive) continue;
				e.second->Update(delta); 
				
			} 
		}
		//Called every tick
		void Tick() 
		{ 
			
			MRT_PROF();
			for (const auto& e : m_SceneEntities) 
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
			for (const auto& e : m_SceneEntities) 
			{
				if (!e.second->IsActive) continue;
				//call its draw function
				e.second->Draw(); 
			}
		}
		
	private:

		Camera* m_MainCamera;

		std::unordered_map<std::string, Ref<Entity>> m_SceneEntities;

	};

}