#pragma once

#ifdef WTF_PLATFORM_WINDOWS
	#ifdef WTF_BUILD_DLL
		#define WTEngine_API __declspec(dllexport)
	#else
		#define WTEngine_API __declspec(dllimport)
	#endif
#else
	#error WTEngine only supports Windows
#endif

#define BIT(x) (1 << x)