#pragma once

#include "core/math/Math.h"
#include "Entity3D.h"


namespace MortarCore {

	class RenderEntity : public Entity3D
	{
	public:

		RenderEntity() : Entity3D("RenderEntity"), m_Model(){}
		RenderEntity(std::string Name) : Entity3D(Name), m_Model() {}
		RenderEntity(std::string Name, Ref<Model>& model) : Entity3D(Name), m_Model(model) {}
		RenderEntity(Ref<Model>& model) : Entity3D(), m_Model(model) {}
		virtual ~RenderEntity() {}

        Ref<Model>& GetModel() { return m_Model; }
		void SetModel(Ref<Model>& m) { m_Model = m; }

		virtual void Update (double delta) override
		{
			Transform.rotation.x += (float)delta * 2.0f;
			Transform.rotation.y += (float)delta * 2.0f;
			Transform.rotation.z += (float)delta * 2.0f;
		}

	private:

        Ref<Model> m_Model;
	};
}
