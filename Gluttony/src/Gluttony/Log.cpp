#include "glpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Gluttony {

	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
    std::string Log::m_ClientLoggerFormat = "[%T - %n] %^%v%$";         // Hardcoded for now - will later maybe be exposed to User
    std::string Log::m_EngineLoggerFormat = "[%T - %n] %^%v%$";                // Engine logging format - can NOT be changed by user

	void Log::Init() {

        // CORE LOGGER
        auto CoreSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        // create log files of verious levels
        auto EngineErrorLogFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("EngineLogs/error.txt");
        EngineErrorLogFileSink->set_level(spdlog::level::warn);
        auto EngineDebugLogFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("EngineLogs/debug.txt");
        EngineDebugLogFileSink->set_level(spdlog::level::debug);

        // Configure CoreLogger
        s_EngineLogger = std::make_shared<spdlog::logger>("GLUTTONY");
        s_EngineLogger->sinks().push_back(CoreSink);
        s_EngineLogger->sinks().push_back(EngineErrorLogFileSink);
        s_EngineLogger->sinks().push_back(EngineDebugLogFileSink);

        s_EngineLogger->set_level(spdlog::level::trace);
        s_EngineLogger->set_pattern(m_EngineLoggerFormat);


        // CLIENT LOGGER
        auto ClientSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        // create log files of verious levels       UNFINISHED - change so user can set LogDestination
        auto debugLogFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("ApplicationLogs/debug.txt");
        debugLogFileSink->set_level(spdlog::level::debug);

        // Configure ClientLogger
        s_ClientLogger = std::make_shared<spdlog::logger>("APP");
        s_ClientLogger->sinks().push_back(ClientSink);
        s_ClientLogger->sinks().push_back(debugLogFileSink);
        
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_pattern(m_ClientLoggerFormat);
        
    }
}
