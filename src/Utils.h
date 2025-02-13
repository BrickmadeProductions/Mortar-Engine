#pragma once

#define GLM_ENABLE_EXPERIMENTAL true
#define MRT_DEBUG true
#define MRT_PROF_ENABLED false

//general
#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>
#include <EASTL/any.h>
#include <EASTL/list.h>
#include <EASTL/shared_ptr.h>

#include <any>
#include <chrono>
#include <thread>
#include <queue>
#include <functional>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <filesystem>
#include <cstdlib>
#include <iostream>
#include <deque>
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
#include <glm/gtx/string_cast.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

#if MRT_DEBUG
    #define MRT_CORE_ASSERT(condition)                                                \
            if (!(condition)) {                                            \
                std::cout << "\033[31mMortar Engine: Assertion Failed: " #condition << " at "       \
                          << __FILE__ << ":" << __LINE__ << std::endl;      \
                std::abort();                                                \
            }                                                             \
        
#else
    #define MRT_CORE_ASSERT(condition)
#endif

#if MRT_PROF_ENABLED
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define MRT_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define MRT_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define MRT_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define MRT_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define MRT_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define MRT_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define MRT_FUNC_SIG __func__
	#else
		#define MRT_FUNC_SIG "MRT_FUNC_SIG unknown!"
	#endif

    #define MRT_PROF() \
    auto start = std::chrono::steady_clock::now(); \
	std::string funName = std::string(__func__) + "()"; \
    struct ProfileGuard { \
		ProfileGuard(std::chrono::steady_clock::time_point& start, std::string name) : start_(start), name_(name) {} \
        ~ProfileGuard() { \
            auto end = std::chrono::steady_clock::now(); \
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count(); \
			double ms = static_cast<double>(duration) / 1000; \
            std::cout << "\033[33mMortar Engine: " << name_ << " Took " << ms << " ms" << std::endl; \
        } \
		std::string name_; \
		std::chrono::steady_clock::time_point start_; \
    } profile_guard(start, funName);
	
	
#else
    #define MRT_PROF()
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


