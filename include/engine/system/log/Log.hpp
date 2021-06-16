#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // for custom types log
#include "engine/system/utils/utils.hpp"



namespace MHelmet {

	struct Log
	{		
		virtual void Init() = 0;

		virtual RefCount<spdlog::logger>& EngineLogger() = 0;
		virtual RefCount<spdlog::logger>& ClientLogger() = 0;

		virtual void ShutDown() = 0;

		inline virtual ~Log() = default;



		
	};

}