#pragma once

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#ifndef TRANSFORM_H
#define TRANSFORM_H

namespace MortarCore {

	struct Transform
	{
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec4 rotation = { 0.0f, 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		Transform() = default;
		Transform(glm::vec3 pos, glm::vec4 rot, glm::vec3 scal) : position(pos), rotation(rot), scale(scal) {}
		Transform(const Transform&) = default;
	};
}
#endif 
