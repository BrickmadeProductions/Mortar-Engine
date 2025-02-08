#pragma once

#include "Utils.h"
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

		//instantiates a blank entity, with a model ref that can be attached
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
			MRT_PRINT("Scene Loading...");
			//TODO load default shaders and materials (move to abstraction later)
			Ref<Shader> defaultShader = Shader::CreateProgram("resource/shader/defaultSpatial.vert", "resource/shader/defaultSpatial.frag");

			MRT_PRINT("Default Shader Loaded...");
			Ref<Material> defaultMat = CreateRef<Material>(defaultShader);
			
			MRT_PRINT("Default Material Loaded...");
			RenderCommands::CacheMaterial(defaultMat);

			for (const auto e : m_GameObjects) e.second->Awake(); 
		}
		//Called every frame
		void Update(double delta) { for (const auto e : m_GameObjects) e.second->Update(delta); }
		//Called every tick
		void Tick() { for (const auto e : m_GameObjects) e.second->Tick(); }
		//Called every time the scene is about to draw
		void Draw() 
		{ 
			//clear screen
			RenderCommands::Clear();

			//draw any meshes here
			//TODO (Optimize)
			for (const auto e : m_GameObjects) 
			{
				//check if it is a render entity
				if (e.second->GetModel() == nullptr) continue;

				//final submit to shaders
				Renderer::Submit(e.second);

				//call its post draw function
				e.second->PostDraw(); 
			}
		}

	private:

		std::unordered_map<uint32_t, Ref<Entity>> m_GameObjects;
		std::unordered_map<std::string, Ref<Entity>> m_GameObjectsByName;

		uint32_t m_InstanceNonce = 0;
	};

}