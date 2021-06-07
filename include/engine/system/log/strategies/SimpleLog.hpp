#pragma once

#include "engine/system/log/Log.hpp"

namespace MHelmet {

	struct SimpleLog : public Log
	{
		inline SimpleLog()
		{ 
			Init();
		}

		void Init() override;

		inline std::shared_ptr<spdlog::logger>& EngineLogger() override
		{
			return m_EngineLogger;
		}
		inline std::shared_ptr<spdlog::logger>& ClientLogger() override
		{
			return m_ClientLogger;
		}

		virtual void ShutDown() override;

		virtual ~SimpleLog();

	private:
		bool m_Alive = false;
		std::shared_ptr<spdlog::logger> m_EngineLogger;
		std::shared_ptr<spdlog::logger> m_ClientLogger;
	};





}