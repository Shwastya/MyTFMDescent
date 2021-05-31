#pragma once

#include "engine/log/log.hpp"

namespace MHelmet {

	struct LogStrategy_1 : public Log
	{

		inline LogStrategy_1() { Init(); }

		void Init() override;

		inline std::shared_ptr<spdlog::logger>& EngineLogger() override
		{
			return m_EngineLogger;
		}
		inline std::shared_ptr<spdlog::logger>& ClientLogger() override
		{
			return m_ClientLogger;
		}

		virtual ~LogStrategy_1() = default;

	private:
		std::shared_ptr<spdlog::logger> m_EngineLogger;
		std::shared_ptr<spdlog::logger> m_ClientLogger;

	};





}