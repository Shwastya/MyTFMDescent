#pragma once
#include "engine/log/log.hpp"
;

namespace MHelmet {

	enum class LogType 
	{
		STRATEGY1, STRATEGY2
	};

	class LogManager
	{
	public:
		~LogManager();

		static LogManager& p();
		Log& log();

		void switchLog(const LogType type);

	private:
		LogManager();

		Log* m_Log = nullptr;

		LogType m_selected = LogType::STRATEGY1;
		
	};
}
#define ENGINE_LOG ::MHelmet::LogManager::p().log().EngineLogger()
#define CLIENT_LOG ::MHelmet::LogManager::p().log().ClientLogger()

#define MH_ENGINE_TRACE(...) ENGINE_LOG->trace (__VA_ARGS__)
#define MH_ENGINE_INFO(...)  ENGINE_LOG->info  (__VA_ARGS__)
#define MH_ENGINE_WARN(...)  ENGINE_LOG->warn  (__VA_ARGS__)
#define MH_ENGINE_ERROR(...) ENGINE_LOG->error (__VA_ARGS__)
#define MH_ENGINE_FATAL(...) ENGINE_LOG->fatal (__VA_ARGS__)

#define MH_CLIENT_TRACE(...) CLIENT_LOG->trace (__VA_ARGS__)
#define MH_CLIENT_INFO(...)  CLIENT_LOG->info  (__VA_ARGS__)
#define MH_CLIENT_WARN(...)  CLIENT_LOG->warn  (__VA_ARGS__)
#define MH_CLIENT_ERROR(...) CLIENT_LOG->error (__VA_ARGS__)
#define MH_CLIENT_FATAL(...) CLIENT_LOG->fatal (__VA_ARGS__)