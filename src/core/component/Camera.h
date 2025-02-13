#pragma once

#include "core/math/Math.h"
#include "core/Window.h"
#include "core/scene/Entity3D.h"

namespace MortarCore {

	class Camera : public Entity3D
	{
	public:
		
		using Entity3D::Entity3D;
		virtual ~Camera();

		//retreives the perspective projection based on the params
	    void UpdateProjections(uint32_t fov, float near, float far);
		glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }

		// bool CanSee(Ref<Entity>& Entity)
		// {
			
		// }


		virtual void Awake() override;
		virtual void Tick() override;
		virtual void Update(double delta) override;


	private:

		//window pointer to access the width, height, etc.
		Window* window;

		//MOVE TO SEPERATE CLASS LATER
		float speed;
		float defaultSpeed;
		float sensitivity;
		bool firstClick = false;
		glm::vec3 moveDirection;
		//MOVE TO SEPERATE CLASS LATER

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
	};
}
