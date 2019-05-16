#pragma once

#ifdef WTF_PLATFORM_WINDOWS
	#ifdef WTF_BUILD_DLL
		#define WTF_API __declspec(dllexport)
	#else
		#define WTF_API __declspec(dllimport)
	#endif
#else
	#error WTEngine only supports Windows
#endif

#ifdef WTF_DEBUG
	#define WTF_ENABLE_ASSERTS
#endif

#ifdef WTF_ENABLE_ASSERTS
	#define WTF_ASSERT(x, ...) { if(!(x)) { WTF_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define WTF_CORE_ASSERT(x, ...) { if(!(x)) { WTF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define WTF_ASSERT(x, ...)	
	#define WTF_CORE_ASSERT(x, ...)
#endif



#define BIT(x) (1 << x)

#define WTF_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)