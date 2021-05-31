#include "engine/log/logManager.hpp"
#include "engine/log/logStrategies/logStrategy1.hpp"

MHelmet::LogManager::LogManager()
{
	m_Log = new LogStrategy_1();
	//m_Log->Init();
}

MHelmet::LogManager::~LogManager()
{
	delete m_Log;
	printf("se borra LogManager\n");
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
	delete m_Log;
	

	if (type == MHelmet::LogType::STRATEGY1)
	{
		if (m_selected != MHelmet::LogType::STRATEGY1)
		{
			
			m_selected = MHelmet::LogType::STRATEGY1;
			m_Log = new LogStrategy_1();

		}
	}
		
	if (type == MHelmet::LogType::STRATEGY2)
	{
		if (m_selected != MHelmet::LogType::STRATEGY2)
		{
			
			m_selected = MHelmet::LogType::STRATEGY2;
			m_Log = new LogStrategy_2();

		}
	}




					
	
	
}
