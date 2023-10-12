#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


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
		inline static std::shared_ptr<spdlog::logger>& getEngineLogger() { return s_EngineLogger; };
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; };

		// Formatting for client
		inline static std::string& getLoggingFormat() { return m_ClientLoggerFormat; };
		inline static void setLoggingFormat(std::string newFormat) { m_ClientLoggerFormat = newFormat; };

	private:

		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::string m_ClientLoggerFormat;
		static std::string m_EngineLoggerFormat;

	};
}


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

