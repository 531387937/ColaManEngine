#pragma once
#ifdef CM_PLATFORM_WINDOWS
	#ifdef CM_BUILD_DLL
		#define CM_API __declspec(dllexport)
	#else
		#define CM_API __declspec(dllimport)
	#endif
#endif