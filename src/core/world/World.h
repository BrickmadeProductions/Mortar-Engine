#pragma once

#include "Core/Component/Camera.h"
#include "Utils.h"

namespace MortarCore {

	class World 
	{
	public:

		World() : m_currentCamera(){}
		~World();

		Camera& GetCamera() { return *m_currentCamera; }

		Model& Instantiate() 
		{
			m_InstanceNonce++;

			//creates a default model object, which can then be modified outside this function
			m_GameObjects.insert(m_InstanceNonce);

			return m_GameObjects[m_InstanceNonce];
		}

		Model& GetObject(uint32_t objectID) { return m_GameObjects[objectID]; }

		virtual void Update(float delta) = 0;
		virtual void Tick() = 0;

	private:

		Camera* m_currentCamera;

		eastl::map<uint32_t, Model&> m_GameObjects;

		uint32_t m_InstanceNonce = 0;
	};
}