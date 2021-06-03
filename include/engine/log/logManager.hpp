#pragma once
#include "engine/log/log.hpp"
;

namespace MHelmet {

	enum class LogType 
	{
		SIMPLE_LOG, OTHER_LOG
	};

	class LogManager
	{
	public:
		~LogManager();

		static LogManager& p();
		Log& GetLog();

		void SwitchLog(const LogType type);

	private:
		LogManager();

		Log* m_Log = nullptr;

		LogType m_selected = LogType::SIMPLE_LOG;
		
	};
}

#define ENGINE_LOG ::MHelmet::LogManager::p().GetLog().EngineLogger()
#define CLIENT_LOG ::MHelmet::LogManager::p().GetLog().ClientLogger()

#define MH_ENGINE_TRACE(...) ENGINE_LOG->trace (__VA_ARGS__)
#define MH_ENGINE_INFO(...)  ENGINE_LOG->info  (__VA_ARGS__)
#define MH_ENGINE_WARN(...)  ENGINE_LOG->warn  (__VA_ARGS__)
#define MH_ENGINE_ERROR(...) ENGINE_LOG->error (__VA_ARGS__)
#define MH_ENGINE_FATAL(...) ENGINE_LOG->fatal (__VA_ARGS__)

#define MH_TRACE(...) CLIENT_LOG->trace (__VA_ARGS__)
#define MH_INFO(...)  CLIENT_LOG->info  (__VA_ARGS__)
#define MH_WARN(...)  CLIENT_LOG->warn  (__VA_ARGS__)
#define MH_ERROR(...) CLIENT_LOG->error (__VA_ARGS__)
#define MH_FATAL(...) CLIENT_LOG->fatal (__VA_ARGS__)