#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace WinterGE
{
	class WGE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Engine log macros
#define WGE_LOG_CRITICAL(...)      ::WinterGE::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define WGE_LOG_ERROR(...)         ::WinterGE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WGE_LOG_WARN(...)          ::WinterGE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WGE_LOG_INFO(...)          ::WinterGE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WGE_LOG_TRACE(...)         ::WinterGE::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define CLIENT_LOG_CRITICAL(...)   ::WinterGE::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CLIENT_LOG_ERROR(...)      ::WinterGE::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_LOG_WARN(...)       ::WinterGE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_LOG_INFO(...)       ::WinterGE::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_LOG_TRACE(...)      ::WinterGE::Log::GetClientLogger()->trace(__VA_ARGS__)