#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Gluttony {

	class GLUTTONY_API Log {
	
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; };

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}


// Logginc macros for CORE
#define GL_CORE_LOG_TRACE(...)   ::Gluttony::Log::getCoreLogger()->trace(__VA_ARGS__);
#define GL_CORE_LOG_INFO(...)    ::Gluttony::Log::getCoreLogger()->info(__VA_ARGS__);
#define GL_CORE_LOG_WARM(...)    ::Gluttony::Log::getCoreLogger()->warn(__VA_ARGS__);
#define GL_CORE_LOG_ERROR(...)   ::Gluttony::Log::getCoreLogger()->error(__VA_ARGS__);
#define GL_CORE_LOG_FATAL(...)   ::Gluttony::Log::getCoreLogger()->fatal(__VA_ARGS__);

// Logginc macros for CLIENT
#define GL_LOG_TRACE(...)	     ::Gluttony::Log::getClientLogger()->trace(__VA_ARGS__);
#define GL_LOG_INFO(...)         ::Gluttony::Log::getClientLogger()->info(__VA_ARGS__);
#define GL_LOG_WARM(...)         ::Gluttony::Log::getClientLogger()->warn(__VA_ARGS__);
#define GL_LOG_ERROR(...)        ::Gluttony::Log::getClientLogger()->error(__VA_ARGS__);
#define GL_LOG_FATAL(...)        ::Gluttony::Log::getClientLogger()->fatal(__VA_ARGS__);
