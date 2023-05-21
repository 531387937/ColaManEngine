#pragma once
#ifdef CM_PLATFORM_WINDOWS
#if CM_DYNAMIC_LINK
	#ifdef CM_BUILD_DLL
		#define CM_API __declspec(dllexport)
	#else
		#define CM_API __declspec(dllimport)
	#endif
#else
	#define CM_API
#endif
#else
	#error CM only supports Windows!
#endif

#ifdef CM_DEBUG
	#define CM_ENABLE_ASSERTS
#endif

#ifdef CM_ENABLE_ASSERTS
	#define CM_ASSERT(x,...){if(!(x)){CM_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
	#define CM_CORE_ASSERT(x,...){if(!(x)){CM_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
#else
	#define CM_ASSERT(x,...)
	#define CM_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<x)

#include "Log.h"