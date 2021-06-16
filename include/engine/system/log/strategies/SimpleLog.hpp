#pragma once

#include "engine/system/log/Log.hpp"

namespace MHelmet {

	struct SimpleLog : public Log
	{
		SimpleLog()
		{ 
			Init();
		}

		void Init() override;

		RefCount<spdlog::logger>& EngineLogger() override
		{
			return m_EngineLogger;
		}
		RefCount<spdlog::logger>& ClientLogger() override
		{
			return m_ClientLogger;
		}

		virtual void ShutDown() override;

		virtual ~SimpleLog();

	private:
		bool m_Alive = false;
		RefCount<spdlog::logger> m_EngineLogger;
		RefCount<spdlog::logger> m_ClientLogger;
	};





}