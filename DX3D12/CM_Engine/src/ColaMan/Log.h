#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace ColaMan {
	class CM_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		Log();

		~Log();
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


#define CM_CORE_ERROR(...) ::ColaMan::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CM_CORE_WARN(...) ::ColaMan::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CM_CORE_INFO(...) ::ColaMan::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CM_CORE_TRACE(...) ::ColaMan::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CM_CORE_FATAL(...) ::ColaMan::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define CM_ERROR(...) ::ColaMan::Log::GetClientLogger()->error(__VA_ARGS__)
#define CM_WARN(...) ::ColaMan::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CM_INFO(...) ::ColaMan::Log::GetClientLogger()->info(__VA_ARGS__)
#define CM_TRACE(...) ::ColaMan::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CM_FATAL(...) ::ColaMan::Log::GetClientLogger()->fatal(__VA_ARGS__)