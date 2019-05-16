#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace WTF {

	class WTF_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
				
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core logging macros
#define WTF_CORE_ERROR(...)	  ::WTF::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WTF_CORE_FATAL(...)	  ::WTF::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define WTF_CORE_INFO(...)	  ::WTF::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WTF_CORE_WARN(...)	  ::WTF::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WTF_CORE_TRACE(...)	  ::WTF::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client logging macros
#define WTF_ERROR(...) ::WTF::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WTF_FATAL(...) ::WTF::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define WTF_INFO(...)  ::WTF::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WTF_WARN(...)  ::WTF::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WTF_TRACE(...) ::WTF::Log::GetCoreLogger()->trace(__VA_ARGS__)