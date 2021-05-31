#include "engine/log/logManager.hpp"
#include "engine/log/logStrategies/logStrategy1.hpp"

MHelmet::LogManager::LogManager()
{
	m_Log = new LogStrategy_1();
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

MHelmet::Log& MHelmet::LogManager::log()
{
	return *m_Log;
}

void MHelmet::LogManager::switchLog(const MHelmet::LogType type)
{
	//	I probably won't use it
}
