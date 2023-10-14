#pragma once

#include "Core.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


namespace Gluttony {

	enum LogLevel {
		Log = 0,
		Trace,
		Success,
		Warning,
		Error,
		Fatal
	};

	class GLUTTONY_API Log {

	public:

		static void Init();

		// 
		static std::shared_ptr<spdlog::logger>& getEngineLogger() { return m_EngineLogger; };
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return m_ClientLogger; };

		// Formatting for client
		static std::string& getLoggingFormat() { return m_ClientLoggerFormat; };
		static void setLoggingFormat(std::string newFormat) { m_ClientLoggerFormat = newFormat; };

	private:

		static std::shared_ptr<spdlog::logger> m_EngineLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
		static std::string m_ClientLoggerFormat;
		static std::string m_EngineLoggerFormat;

	};

}
/*
// Core log macros
#define GL_CORE_TRACE(...)    ::Gluttony::Log::getEngineLogger()->trace(__VA_ARGS__)
#define GL_CORE_INFO(...)     ::Gluttony::Log::getEngineLogger()->info(__VA_ARGS__)
#define GL_CORE_WARN(...)     ::Gluttony::Log::getEngineLogger()->warn(__VA_ARGS__)
#define GL_CORE_ERROR(...)    ::Gluttony::Log::getEngineLogger()->error(__VA_ARGS__)
#define GL_CORE_CRITICAL(...) ::Gluttony::Log::getEngineLogger()->critical(__VA_ARGS__)

// Client log macros
#define GL_TRACE(...)         ::Gluttony::Log::getClientLogger()->trace(__VA_ARGS__)
#define GL_INFO(...)          ::Gluttony::Log::getClientLogger()->info(__VA_ARGS__)
#define GL_WARN(...)          ::Gluttony::Log::getClientLogger()->warn(__VA_ARGS__)
#define GL_ERROR(...)         ::Gluttony::Log::getClientLogger()->error(__VA_ARGS__)
#define GL_CRITICAL(...)      ::Gluttony::Log::getClientLogger()->critical(__VA_ARGS__)*/


// Redefine LogLevels of spdlog to custom levels  ==>		Log, Trace, Success, Warning, Error, Fatal
#define LOG_LEVEL(Level)			LV_##Level

#define LV_Log			spdlog::level::trace
#define LV_Trace		spdlog::level::debug
#define LV_Success		spdlog::level::info
#define LV_Warning		spdlog::level::warn
#define LV_Error		spdlog::level::err
#define LV_Fatal		spdlog::level::critical

// Logging macro for CLIENT
#define GL_LOG(Level,...)		::Gluttony::Log::getClientLogger()->log(LOG_LEVEL(Level), __VA_ARGS__)


// Logging macroa for CORE

#define GL_CORE_LOG(...)		::Gluttony::Log::getEngineLogger()->log(spdlog::level::trace,__VA_ARGS__)
#define GL_CORE_TRACE(...)		::Gluttony::Log::getEngineLogger()->log(spdlog::level::debug,__VA_ARGS__)
#define GL_CORE_SUCCESS(...)	::Gluttony::Log::getEngineLogger()->log(spdlog::level::info,__VA_ARGS__)
#define GL_CORE_WARN(...)		::Gluttony::Log::getEngineLogger()->log(spdlog::level::warn, __VA_ARGS__)
#define GL_CORE_ERROR(...)		::Gluttony::Log::getEngineLogger()->log(spdlog::level::err, __VA_ARGS__)
#define GL_CORE_FATAL(...)		::Gluttony::Log::getEngineLogger()->log(spdlog::level::critical, __VA_ARGS__)
