#pragma once
#include "engine/system/log/Log.hpp"
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




