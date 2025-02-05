#include "Camera.h"


namespace MortarCore {

	Camera::Camera(Transform t)
	{
		speed = 0.1f;
		isMoving = false;
		moveDirection = glm::vec3(0);

		transform = t;
	}

	void Camera::UpdateProjections(float fov, float near, float far)
	{
		m_ProjectionMatrix = glm::perspectiveFov(glm::radians(fov), (float)Application::Get().GetWindow().GetWidth(), (float)Application::Get().GetWindow().GetHeight(), near, far); 
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::Update() {

		std::string total(std::string("Rydget Engine v0.1 | Camera Location: ") + std::to_string(transform.position.x) + ", " + std::to_string(transform.position.y) + ", " + std::to_string(transform.position.z));

		float curSpeedX = 0.0f;
		float curSpeedY = 0.0f;
		float curSpeedZ = 0.0f;

		isMoving = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);

		glfwSetWindowTitle(window, total.c_str());

		// Handles key inputs
		if (glfwGetKey(window, GLFW_KEY_W)) {

			curSpeedX = speed;

		}

		if (glfwGetKey(window, GLFW_KEY_A)) {

			curSpeedY = speed;
		}

		if (glfwGetKey(window, GLFW_KEY_S)) {

			curSpeedX = -speed;
		}

		if (glfwGetKey(window, GLFW_KEY_D)) {


			curSpeedY = -speed;
		}


		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {

			curSpeedZ = -speed;

		}

		if (glfwGetKey(window, GLFW_KEY_SPACE)) {

			curSpeedZ = speed;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			speed = 0.05f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
		{
			speed = 0.1f;
		}
		else {

			moveDirection = glm::vec3(0);

		}

		moveDirection = (getForward(transform) * curSpeedX) + (getLeft(transform) * curSpeedY);

		moveDirection = moveDirection + (glm::vec3(0, 1, 0) * curSpeedZ);


		if (moveDirection != glm::vec3(0))
			moveDirection = glm::normalize(moveDirection);

		//transform.position = Vector3.add(transform.position, (moveDirection * speed) * Time.deltaTime);
		//std::cout << glm::to_string(moveDirection * speed) << std::endl;

		transform.position += (moveDirection * speed);

		// Handles mouse inputs
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{

			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2.0f), (height / 2.0f));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX;
			double mouseY;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = sensitivity * (float)(mouseY - (height / 2.0f)) / height;
			float rotY = sensitivity * (float)(mouseX - (width / 2.0f)) / width;

			// Calculates upcoming vertical change in the Orientation


			// Decides whether or not the next vertical Orientation is legal or not
			//transform.rotation = newOrientation;

			// Rotates the Orientation left and right
			transform.rotation.x += rotX;
			transform.rotation.y += rotY;
			transform.rotation.x = std::clamp(transform.rotation.x, -90.0f, 90.0f);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(window, (width / 2.0f), (height / 2.0f));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}
	}



}




