#include "engine/log/LogManager.hpp"
#include "engine/log/strategies/SimpleLog.hpp"

MHelmet::LogManager::LogManager()
{
	m_Log = new SimpleLog();
}

MHelmet::LogManager::~LogManager()
{
	delete m_Log;
}

MHelmet::LogManager& MHelmet::LogManager::p()
{
	static MHelmet::LogManager instance;
	return instance;
}

MHelmet::Log& MHelmet::LogManager::GetLog()
{
	return *m_Log;
}

void MHelmet::LogManager::SwitchLog(const MHelmet::LogType type)
{
	//	I probably won't use it
}
