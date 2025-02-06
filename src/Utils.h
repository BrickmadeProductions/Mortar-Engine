#pragma once

#define GLM_ENABLE_EXPERIMENTAL true
#define MTR_DEBUG true

//general
#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>
#include <EASTL/any.h>
#include <EASTL/list.h>
#include <EASTL/shared_ptr.h>

#include <cstdlib>
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
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

#if MTR_DEBUG
    #define MRT_CORE_ASSERT(condition)                                                \
            if (!(condition)) {                                            \
                std::cout << "\033[31mMORTAR ASSERT FAILED: " #condition << " at "       \
                          << __FILE__ << ":" << __LINE__ << std::endl;      \
                std::abort();                                                \
            }                                                             \
        
#else
    #define MRT_CORE_ASSERT(condition)
#endif

#define MRT_PRINT(msg) std::cout << "\033[0mMortar Engine: "; print_value(msg);
#define MRT_PRINT_WARN(msg) std::cout << "\033[33mMortar Engine: "; print_value(msg);
#define MRT_PRINT_ERR(msg) std::cout << "\033[31mMortar Engine: "; print_value(msg);

#ifdef _WIN32
    #define MRT_STARTUP() system("cls")
#else
    #define MRT_STARTUP() system("clear")
#endif

//static methods and constexpr
namespace MortarCore
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	// Helper function to print basic types (int, float, etc.)
	template <typename T>
	static void print_value(const T& value) {
		std::cout << value << std::endl;
	}

	// Specialization for std::string
	template <>
	static void print_value(const std::string& value) {
		std::cout << "\"" << value << "\"" << std::endl;
	}

	// Specialization for other types like containers (e.g., std::vector)
	template <typename T>
	static void print_value(const std::vector<T>& value) {
		std::cout << "[ ";
		for (const auto& item : value) {
			std::cout << item << " ";
		}
		std::cout << "]" << std::endl;
	}
};


