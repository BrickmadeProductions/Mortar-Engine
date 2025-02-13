#include "Camera.h"
#include "core/Application.h"

namespace MortarCore {

    Camera::~Camera()
    {
    }

	void Camera::Awake()
	{
		speed = 0.2f;
		defaultSpeed = speed;
		sensitivity = 50.0f;
		moveDirection = glm::vec3(0);

		window = &Application::GetWindow();
	}

    void Camera::Tick()
    {
    
	}

    void Camera::Update(double delta) 
	{
		float curSpeedX = 0.0f;
		float curSpeedY = 0.0f;
		float curSpeedZ = 0.0f;

		// bool isMoving = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS
		// 	|| glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		// 	|| glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS
		// 	|| glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		// 	|| glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
		// 	|| glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);

		// Handles key inputs
		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_W)) {

			curSpeedX = speed;

		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_A)) {

			curSpeedY = speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_S)) {

			curSpeedX = -speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_D)) {


			curSpeedY = -speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_LEFT_CONTROL)) {

			curSpeedZ = -speed;

		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_SPACE)) {

			curSpeedZ = speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = defaultSpeed * 5.0f;
		}
		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			speed = defaultSpeed;
		}
		else {

			moveDirection = glm::vec3(0);

		}

		moveDirection = (MRTMath::getForward(Transform) * curSpeedX) + (MRTMath::getLeft(Transform) * curSpeedY);

		moveDirection = moveDirection + (glm::vec3(0, 1, 0) * curSpeedZ);

		if (moveDirection != glm::vec3(0))
			moveDirection = glm::normalize(moveDirection);


		Transform.position += (moveDirection * speed) * (float)delta * 100.0f;

		// Handles mouse inputs
		if (glfwGetMouseButton(window->GetNativeWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{

			// Hides mouse cursor
			glfwSetInputMode(window->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(window->GetNativeWindow(), (window->GetWidth() / 2.0f), (window->GetHeight() / 2.0f));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX;
			double mouseY;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window->GetNativeWindow(), &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "Transforms" them into degrees 
			float rotX = sensitivity * (float)(mouseY - (window->GetHeight() / 2.0f)) / window->GetHeight();
			float rotY = sensitivity * (float)(mouseX - (window->GetWidth() / 2.0f)) / window->GetWidth();

			// Calculates upcoming vertical change in the Orientation


			// Decides whether or not the next vertical Orientation is legal or not
			//Transform.rotation = newOrientation;

			// Rotates the Orientation left and right
			Transform.rotation.x += rotX;
			Transform.rotation.y += rotY;
			Transform.rotation.x = std::clamp(Transform.rotation.x, -89.9f, 89.9f);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(window->GetNativeWindow(), (window->GetWidth() / 2.0f), (window->GetHeight() / 2.0f));
		}
		else if (glfwGetMouseButton(window->GetNativeWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}

		UpdateProjections(60, 0.1f, 10000.0f);
	}

    void Camera::UpdateProjections(uint32_t fov, float near, float far)
    {
		m_ProjectionMatrix = glm::perspectiveFov(glm::radians((float)fov), (float)window->GetWidth(), (float)window->GetHeight(), near, far);
		m_ViewMatrix = MRTMath::getViewMatrix(Transform);
	}



}




