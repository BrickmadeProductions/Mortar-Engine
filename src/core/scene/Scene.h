#pragma once

#include "Utils.h"
#include "core/scene/Entity.h"

namespace MortarCore {

	class Scene 
	{
	public:

		Scene() = default;
		Scene(const Scene& scene) = default;
		~Scene() = default;

		template <class Entity>
		Ref<Entity> Instantiate() 
		{
			m_InstanceNonce++;

			m_GameObjects.emplace(m_InstanceNonce, CreateRef<Entity>());

			return m_GameObjects[m_InstanceNonce];
		}

		Ref<Entity> GetObject(uint32_t objectID) { return m_GameObjects[objectID]; }

		virtual void Update(double delta) { for (const auto e : m_GameObjects) e.second->Update(); }
		virtual void Tick() { for (const auto e : m_GameObjects) e.second->Tick(); }
		virtual void Draw() { for (const auto e : m_GameObjects) e.second->Draw(); }

	private:

		std::unordered_map<uint32_t, Ref<Entity>> m_GameObjects;
		uint32_t m_InstanceNonce = 0;
	};
}