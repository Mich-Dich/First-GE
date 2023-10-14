#pragma once

#ifdef GL_PLATFORM_WINDOWS

	#ifdef GL_BUILD_DLL
		#define GLUTTONY_API __declspec(dllexport)
	#else
		#define GLUTTONY_API __declspec(dllimport)
	#endif
#else
	#error Gluttony only supports Windows!
#endif

#ifdef GL_CORE_ASSERTS
	#define GL_CORE_ASSERT(x, ...)	{ if (!(x)) { GL_CORE_ERROR("Assertion Failes: {0}", __VA_ARGS__), __debugbreak; } }
	#define GL_ASSERT(x, ...)		{ if (!(x)) { GL_ERROR(error, "Assertion Failes: {0}", __VA_ARGS__), __debugbreak; } }
#else
	#define GL_CORE_ASSERT(x, ...)
	#define GL_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)