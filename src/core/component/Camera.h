#pragma once

#include "Utils.h"
#include "core/math/Transform.h"

namespace MortarCore {

	class Camera
	{
	public:

		Transform transform;

		Camera(Transform transform);
		Camera(const Camera&) = default;

		//retreives the perspective projection based on the params
	    void UpdateProjections(float fov, float near, float far);

		void Update();

	private:

		//MOVE TO SEPERATE CLASS LATER
		float speed;
		glm::vec3 moveDirection;
		//MOVE TO SEPERATE CLASS LATER

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}
