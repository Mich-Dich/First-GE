
#include "glpch.h"
#include "Gluttony/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Gluttony {


    std::shared_ptr<spdlog::logger> Log::m_EngineLogger;
    std::shared_ptr<spdlog::logger> Log::m_ClientLogger;
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
        m_EngineLogger = std::make_shared<spdlog::logger>("GLUTTONY");
        m_EngineLogger->sinks().push_back(CoreSink);
        m_EngineLogger->sinks().push_back(EngineErrorLogFileSink);
        m_EngineLogger->sinks().push_back(EngineDebugLogFileSink);

        m_EngineLogger->set_level(spdlog::level::trace);
        m_EngineLogger->set_pattern(m_EngineLoggerFormat);


        // CLIENT LOGGER
        auto ClientSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        // create log files of verious levels       UNFINISHED - change so user can set LogDestination
        auto debugLogFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("ApplicationLogs/debug.txt");
        debugLogFileSink->set_level(spdlog::level::debug);

        // Configure ClientLogger
        m_ClientLogger = std::make_shared<spdlog::logger>("APP");
        m_ClientLogger->sinks().push_back(ClientSink);
        m_ClientLogger->sinks().push_back(debugLogFileSink);

        m_ClientLogger->set_level(spdlog::level::trace);
        m_ClientLogger->set_pattern(m_ClientLoggerFormat);

    }

}

/*
namespace Gluttony {

}*/