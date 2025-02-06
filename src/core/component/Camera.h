#pragma once

#include "core/math/Math.h"
#include "core/Application.h"

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

		//window reference to access the width, height, etc.
		Window& window;

		//MOVE TO SEPERATE CLASS LATER
		float speed;
		float sensitivity = 0.5f;
		bool firstClick = false;
		glm::vec3 moveDirection;
		//MOVE TO SEPERATE CLASS LATER

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}
