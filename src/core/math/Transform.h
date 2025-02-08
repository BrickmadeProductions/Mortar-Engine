#pragma once

#include "Utils.h"

namespace MortarCore {

	struct Transform
	{
	public:
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		Transform() = default;
		Transform(glm::vec3 pos, glm::vec4 rot, glm::vec3 scal) : position(pos), rotation(rot), scale(scal) {}
		Transform(const Transform&) = default;
		
		glm::mat4 GetTransformMatrix() 
		{ 
			glm::mat4 transformMatrix = glm::mat4(1.0f);  // Always start with the identity matrix

			// Apply translation (position)
			transformMatrix = glm::translate(transformMatrix, position);
	
			// Apply rotation (pitch, yaw, roll)
			transformMatrix = glm::rotate(transformMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));  // Roll (X-axis)
			transformMatrix = glm::rotate(transformMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));  // Pitch (Y-axis)
			transformMatrix = glm::rotate(transformMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));  // Yaw (Z-axis)
	
			// Apply scale
			transformMatrix = glm::scale(transformMatrix, scale);

			return transformMatrix;  // Return the final transformation matrix
		}
	};
}
