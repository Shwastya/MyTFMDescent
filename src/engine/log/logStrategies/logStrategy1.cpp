#include "engine/log/logStrategies/logStrategy1.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace MHelmet {

	//std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	//std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void LogStrategy_1::Init()
	{
		/* STRING FORMAT EXAMPLES: */
		// %^ - Start color range (can be used only once)
		// %T - ISO 8601 time format (HH::MM::SS)
		// %n - Logger's name
		// %v - The actual text to log
		// %$ - End color range   (can be use only once)

		// MORE: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting

		spdlog::set_pattern("%^[%T] %n: %v%$");

		/* LEVEL ENUM */

		//	trace    = SPDLOG_LEVEL_TRACE,
		//	debug    = SPDLOG_LEVEL_DEBUG,
		//	info     = SPDLOG_LEVEL_INFO,
		//	warn     = SPDLOG_LEVEL_WARN,
		//	err      = SPDLOG_LEVEL_ERROR,
		//	critical = SPDLOG_LEVEL_CRITICAL,
		//	off      = SPDLOG_LEVEL_OFF,
		//	n_levels

		m_CoreLogger = spdlog::stdout_color_mt("MHELMET");
		m_CoreLogger->set_level(spdlog::level::trace);

		m_ClientLogger = spdlog::stdout_color_mt("PROJECT");
		m_ClientLogger->set_level(spdlog::level::trace);		
	}

	std::shared_ptr<spdlog::logger>& LogStrategy_1::GetCoreLogger()
	{
		return m_CoreLogger;
	}
	std::shared_ptr<spdlog::logger>& LogStrategy_1::GetClientLogger()
	{
		return m_ClientLogger;
	}







	void LogStrategy_2::Init()
	{

		spdlog::set_pattern("%^-%T- %n: %v%$");

		m_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		m_CoreLogger->set_level(spdlog::level::trace);

		m_ClientLogger = spdlog::stdout_color_mt("APP");
		m_ClientLogger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& LogStrategy_2::GetCoreLogger()
	{
		return m_CoreLogger;
	}
	std::shared_ptr<spdlog::logger>& LogStrategy_2::GetClientLogger()
	{
		return m_ClientLogger;
	}

}