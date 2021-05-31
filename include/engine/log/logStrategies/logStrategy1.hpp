#pragma once

#include "engine/log/log.hpp"

namespace MHelmet {

	struct LogStrategy_1 : public Log
	{

		inline LogStrategy_1() { Init(); }

		void Init() override;

		std::shared_ptr<spdlog::logger>& GetCoreLogger() override;
		std::shared_ptr<spdlog::logger>& GetClientLogger() override;

		virtual ~LogStrategy_1() 
		{
			printf("Se destruye LogStrategy_1\n");
		}

	private:
		std::shared_ptr<spdlog::logger> m_CoreLogger;
		std::shared_ptr<spdlog::logger> m_ClientLogger;

	};







	struct LogStrategy_2 : public Log
	{
		inline LogStrategy_2() { Init(); }

		void Init() override;

		std::shared_ptr<spdlog::logger>& GetCoreLogger() override;
		std::shared_ptr<spdlog::logger>& GetClientLogger() override;

		virtual ~LogStrategy_2() 
		{
			printf("Se destruye LogStrategy_2\n");
		}

	private:
		std::shared_ptr<spdlog::logger> m_CoreLogger;
		std::shared_ptr<spdlog::logger> m_ClientLogger;

	};

}