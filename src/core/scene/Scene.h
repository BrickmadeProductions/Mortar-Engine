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

		Scene() 
		{
			//TODO load default shaders and materials (move to abstraction later)
			Ref<Shader> defaultShader = Shader::CreateProgram("resource/shader/defaultSpatial.vert", "resource/shader/defaultSpatial.frag");

			MRT_PRINT("Default Shader Loaded...");
			Ref<Material> defaultMat = CreateRef<Material>(defaultShader);
			
			MRT_PRINT("Default Material Loaded...");
			RenderCommands::CacheMaterial(defaultMat);
		}
		
		Scene(const Scene& scene) = default;
		~Scene() = default;

		static Camera* GetCameraCurrent();

		//Instantiates a blank entity of type T
		template <class T>
		Ref<T> Instantiate(std::string name) 
		{
			if (m_GameObjectsByName.contains(name)) 
			{
				MRT_PRINT_ERR("ENTITY WITH THIS NAME ALREADY EXISTS")
				return nullptr;
			}
			
			m_InstanceNonce++;
			
			Ref<T> entity = CreateRef<T>(name);

			//add the ref to both maps
			m_GameObjects.emplace(m_InstanceNonce, entity);
			m_GameObjectsByName.emplace(name, entity);
			
			//Call the awake function
			entity->Awake();

			MRT_PRINT("Entity " + std::string(typeid(T).name()) + " Instantiated With ID: " + std::to_string(m_InstanceNonce));

			return entity;
		}

		//Instantiates a batch of entities based on the model inserted (they will be drawn in one call)
		template <class T>
		Ref<RenderBatch> InstantiateBatch(std::string EntityName, Ref<Model> model, int amount) 
		{			
			std::vector<Ref<T>> batchEntites;
			for (int i = 0; i < amount; i++)
			{
				Ref<T> entity = Instantiate<T>(std::string(EntityName + std::to_string(i)));
				entity->SetModel(model);

				batchEntites.push_back(entity);
			}

			Ref<RenderBatch> batch = CreateRef<RenderBatch>(batchEntites);
			m_RenderBatches.push_back(batch);

			return batch;
			
		}

		template <typename T>
		Ref<T> GetEntity(uint32_t objectID) { return m_GameObjects[objectID]; }
		
		template <typename T>
		Ref<T> GetEntity(std::string name) { return m_GameObjectsByName[name]; }
		
		template <typename T>
		Ref<T> GetEntity() 
		{ 
			for (const auto& entityPair : m_GameObjects) 
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
			for (const auto& entityPair : m_GameObjects) 
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
			for (const auto& e : m_GameObjects) 
			{
				if (!e.second->IsActive) continue;
				//get current camera by last active
				else if (e.second->IsEntityOfType<Camera>()) {
					m_MainCamera = e.second->Get<Camera>();
				}

				e.second->Awake(); 
			}
		}
		//Called every frame
		void Update(double delta) 
		{ 
			MRT_PROF();
			for (const auto& e : m_GameObjects) 
			{
				if (!e.second->IsActive) continue;
				e.second->Update(delta); 
				
			} 
		}
		//Called every tick
		void Tick() 
		{ 
			
			MRT_PROF();
			for (const auto& e : m_GameObjects) 
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
			for (auto& rb : m_RenderBatches) Renderer::Submit(rb);

			for (const auto& e : m_GameObjects) 
			{
				if (!e.second->IsActive) continue;

				//call its post draw function
				e.second->PostDraw(); 
			}
		}
		
	private:

		Camera* m_MainCamera;

		std::unordered_map<uint32_t, Ref<Entity>> m_GameObjects;
		std::unordered_map<std::string, Ref<Entity>> m_GameObjectsByName;

		std::vector<Ref<RenderBatch>> m_RenderBatches;

		uint32_t m_InstanceNonce = 0;
	};

}