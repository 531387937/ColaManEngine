#include "hzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ColaMan {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger = nullptr;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("ColaMan");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	Log::Log()
	{

	}

	Log::~Log()
	{

	}
}