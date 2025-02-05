#pragma once

#define GLM_ENABLE_EXPERIMENTAL true
#define OPENGL_DEBUG_ON true
#define VULKAN_DEBUG_ON false

//general
#include <EASTL/vector.h>
#include <EASTL/map.h>
#include <EASTL/any.h>
#include <EASTL/list.h>
#include <EASTL/shared_ptr.h>

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <utility>
#include <functional>
#include <memory>
#include <algorithm>

//rendering
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//mathmatics
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace MortarCore
{
	template<typename T>
	using Ref = eastl::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return eastl::make_shared<T>(eastl::forward<Args>(args)...);
	}
};


#if OPENGL_DEBUG_ON 
#define OPEN_GL_DEBUG(x) x
#else 
#define OPEN_GL_DEBUG(x)
#endif

#if VULKAN_DEBUG_ON 
#define VULKAN_DEBUG(x) x
#else 
#define VULKAN_DEBUG(x)
#endif

