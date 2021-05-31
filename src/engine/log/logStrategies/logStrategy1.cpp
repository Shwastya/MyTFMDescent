#include "engine/log/logStrategies/logStrategy1.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace MHelmet 
{
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

		m_EngineLogger = spdlog::stdout_color_mt("MHELMET");
		m_EngineLogger->set_level(spdlog::level::trace);

		m_ClientLogger = spdlog::stdout_color_mt("PROJECT");
		m_ClientLogger->set_level(spdlog::level::trace);		
	}
}