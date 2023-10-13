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


// Redefine LogLevels of spdlog to be used as variable
#define LOG_LEVEL(Level)			LOG_LV_##Level

#define LOG_LV_Log			spdlog::level::trace
#define LOG_LV_Trace		spdlog::level::debug
#define LOG_LV_Success		spdlog::level::info
#define LOG_LV_Warning		spdlog::level::warn
#define LOG_LV_Error		spdlog::level::err
#define LOG_LV_Fatal		spdlog::level::critical


// Logging macro for CORE
#define GL_CORE_LOG(Level,...)		::Gluttony::Log::getEngineLogger()->log(LOG_LEVEL(Level), __VA_ARGS__)

// Logging macro for CLIENT
#define GL_LOG(Level,...)		::Gluttony::Log::getClientLogger()->log(LOG_LEVEL(Level), __VA_ARGS__)


