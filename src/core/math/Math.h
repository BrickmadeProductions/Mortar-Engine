#pragma once

#include "core/math/Transform.h"
#include "Utils.h"

namespace MortarCore {


	static const float clampF(const float val, const float min, const float max) {

		return std::fmax(min, std::fmin(max, val));
	}

	static const glm::mat4x4 getTransformationMatrix(const Transform& transform) {

		glm::mat4x4 transformation = glm::mat4x4(1.0);

		transformation = glm::translate(transformation, transform.position);
		transformation = glm::rotate(transformation, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
		transformation = glm::rotate(transformation, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
		transformation = glm::rotate(transformation, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
		transformation = glm::scale(transformation, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));

		return transformation;
	}

	static const glm::vec3 getLeft(const Transform& transform) {

		glm::mat4x4 transformMatrix = getTransformationMatrix(transform);

		glm::vec3 left = -glm::vec3(glm::row(transformMatrix, 0));

		return left;

	}

	static const glm::vec3 getUp(const Transform& transform) {

		glm::mat4x4 transformMatrix = getTransformationMatrix(transform);

		glm::vec3 up = glm::vec3(glm::row(transformMatrix, 1));

		return up;

	}

	static const glm::vec3 getForward(const Transform& transform) {

		glm::mat4x4 transformMatrix = getTransformationMatrix(transform);

		glm::vec3 forward = -glm::vec3(glm::row(transformMatrix, 2));

		return forward;

	}

	static const glm::mat4x4 getViewMatrix(const Transform& transform) {

		return glm::lookAt(transform.position, transform.position + getForward(transform), glm::vec3(0,1,0));
	}


	
	
}

