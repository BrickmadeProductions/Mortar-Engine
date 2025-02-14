#include "Camera.h"
#include "core/Application.h"

namespace MortarCore {

    Camera::~Camera()
    {
    }


	void Camera::Awake()
	{
		Speed = 0.2f;
		m_DefaultSpeed = Speed;
		m_Sensitivity = 50.0f;
		m_MoveDirection = glm::vec3(0);
		SetClearColor(0.5f, 0.8f, 0.9f);
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

			curSpeedX = Speed;

		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_A)) {

			curSpeedY = Speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_S)) {

			curSpeedX = -Speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_D)) {


			curSpeedY = -Speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_LEFT_CONTROL)) {

			curSpeedZ = -Speed;

		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_SPACE)) {

			curSpeedZ = Speed;
		}

		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			Speed = m_DefaultSpeed * 5.0f;
		}
		if (glfwGetKey(window->GetNativeWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			Speed = m_DefaultSpeed;
		}
		else {

			m_MoveDirection = glm::vec3(0);

		}

		m_MoveDirection = (MRTMath::getForward(Transform) * curSpeedX) + (MRTMath::getLeft(Transform) * curSpeedY);

		m_MoveDirection = m_MoveDirection + (glm::vec3(0, 1, 0) * curSpeedZ);

		if (m_MoveDirection != glm::vec3(0))
			m_MoveDirection = glm::normalize(m_MoveDirection);


		Transform.position += (m_MoveDirection * Speed) * (float)delta * 100.0f;

		// Handles mouse inputs
		if (glfwGetMouseButton(window->GetNativeWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{

			// Hides mouse cursor
			glfwSetInputMode(window->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (m_FirstClick)
			{
				glfwSetCursorPos(window->GetNativeWindow(), (window->GetWidth() / 2.0f), (window->GetHeight() / 2.0f));
				m_FirstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX;
			double mouseY;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window->GetNativeWindow(), &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "Transforms" them into degrees 
			float rotX = m_Sensitivity * (float)(mouseY - (window->GetHeight() / 2.0f)) / window->GetHeight();
			float rotY = m_Sensitivity * (float)(mouseX - (window->GetWidth() / 2.0f)) / window->GetWidth();

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
			m_FirstClick = true;
		}

		UpdateProjections(60, 0.1f, 10000.0f);
	}

    void Camera::UpdateProjections(uint32_t fov, float near, float far)
    {
		m_ProjectionMatrix = glm::perspectiveFov(glm::radians((float)fov), (float)window->GetWidth(), (float)window->GetHeight(), near, far);
		m_ViewMatrix = MRTMath::getViewMatrix(Transform);
	}

	void Camera::SetClearColor(float r, float g, float b)
	{
		RenderCommands::SetClearColor(glm::vec4(r, g, b, 1.0f));
	}

}




