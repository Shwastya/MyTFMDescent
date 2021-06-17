#pragma once
#include "../MHSetup.hpp"

#if MH_LOG_SYSTEM

	#include "engine/system/log/LogManager.hpp"

	#define ENGINE_LOG ::MHelmet::LogManager::p().GetLog().EngineLogger()
	#define CLIENT_LOG ::MHelmet::LogManager::p().GetLog().ClientLogger()	
	#define CLOSE__LOG ::MHelmet::LogManager::p().GetLog().ShutDown()

	// CORE Logs

		#define CORE_TRACE(...) ENGINE_LOG->trace (__VA_ARGS__)
		#define CORE_INFO(...)  ENGINE_LOG->info  (__VA_ARGS__)
		#define CORE_WARN(...)  ENGINE_LOG->warn  (__VA_ARGS__)
		#define CORE_ERROR(...) ENGINE_LOG->error (__VA_ARGS__)
		#define CORE_FATAL(...) ENGINE_LOG->fatal (__VA_ARGS__)


	// CORE Client

		#define TRACE(...) CLIENT_LOG->trace (__VA_ARGS__)
		#define INFO(...)  CLIENT_LOG->info  (__VA_ARGS__)
		#define WARN(...)  CLIENT_LOG->warn  (__VA_ARGS__)
		#define ERROR(...) CLIENT_LOG->error (__VA_ARGS__)
		#define FATAL(...) CLIENT_LOG->fatal (__VA_ARGS__)

#else
	// CORE Logs
	#define CORE_TRACE(...) 
	#define CORE_INFO(...)  
	#define CORE_WARN(...)  
	#define CORE_ERROR(...) 
	#define CORE_FATAL(...) 
	// CORE Client
	#define TRACE(...)
	#define INFO(...)  
	#define WARN(...)  
	#define ERROR(...) 
	#define FATAL(...) 

#endif // MH_LOG_SYSTEM

namespace CORE
{
	inline void Init() { CORE_TRACE(MH_ENGINE, MH_VERSION); } // Log Singleton init in first use
	inline void Stop() { CORE_TRACE("Shutdown MHelmet Engine"); CLOSE__LOG; }
}

// Perform Event Tasks
#define BindEventFunction(E)   std::bind(&##E, this, std::placeholders::_1)
#define BINDIMGUIEVENT(x) std::bind(&ImGuiLayer::x, this, std::placeholders::_1)


