#pragma once

#include <spdlog/spdlog.h>

namespace MHelmet {

	struct Log
	{		

		virtual void Init() = 0;

		virtual std::shared_ptr<spdlog::logger>& GetCoreLogger()   = 0;
		virtual std::shared_ptr<spdlog::logger>& GetClientLogger() = 0;

		inline virtual ~Log() {};

	private:
		// static std::shared_ptr<spdlog::logger> s_CoreLogger;
		// static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}