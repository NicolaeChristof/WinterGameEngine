#pragma once

#ifdef WGE_PLATFORM_WINDOWS
	#ifdef WGE_BUILD_DLL
		#define WGE_API __declspec(dllexport)
	#else
		#define WGE_API __declspec(dllimport)
	#endif
#else
#error Winter Game Engine only supports Windows!
#endif //  WGE_PLATFORM_WINDOWS


#ifdef  WGE_ENABLE_ASSERTS
	#define WGE_ASSERT(x, ...) { if (!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define WGE_CORE_ASSERT(x, ...) { if (!(x)) { LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define WGE_ASSERT(x, ...)
	#define WGE_CORE_ASSERT(x, ...)
#endif //  WGE_ENABLE_ASSERTS

// std::bind creates a callable function object called a functor
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)