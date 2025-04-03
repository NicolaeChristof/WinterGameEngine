#pragma once

#ifdef WGE_PLATFORM_WINDOWS
	#ifdef WGE_BUILD_DLL
		#define WGE_API __declspec(dllexport)
	#else
		#define WGE_API __declspec(dllimport)
	#endif
#else
#error Winter Game Engine only supports Windows!
#endif