#pragma once
#include "MHSetup.hpp"
#include <MHpch.h>

namespace CORE 
{
	
}

#if MH_LOG_SYSTEM

	#include "engine/log/LogManager.hpp"

	#define ENGINE_LOG ::MHelmet::LogManager::p().GetLog().EngineLogger()
	#define CLIENT_LOG ::MHelmet::LogManager::p().GetLog().ClientLogger()	
	#define CLOSE__LOG ::MHelmet::LogManager::p().GetLog().ShutDown()

	// CORE Logs

		#define MH_CORE_TRACE(...) ENGINE_LOG->trace (__VA_ARGS__)
		#define MH_CORE_INFO(...)  ENGINE_LOG->info  (__VA_ARGS__)
		#define MH_CORE_WARN(...)  ENGINE_LOG->warn  (__VA_ARGS__)
		#define MH_CORE_ERROR(...) ENGINE_LOG->error (__VA_ARGS__)
		#define MH_CORE_FATAL(...) ENGINE_LOG->fatal (__VA_ARGS__)


	// CORE Client

		#define MH_TRACE(...) CLIENT_LOG->trace (__VA_ARGS__)
		#define MH_INFO(...)  CLIENT_LOG->info  (__VA_ARGS__)
		#define MH_WARN(...)  CLIENT_LOG->warn  (__VA_ARGS__)
		#define MH_ERROR(...) CLIENT_LOG->error (__VA_ARGS__)
		#define MH_FATAL(...) CLIENT_LOG->fatal (__VA_ARGS__)

#else
	// CORE Logs
	#define MH_CORE_TRACE(...) 
	#define MH_CORE_INFO(...)  
	#define MH_CORE_WARN(...)  
	#define MH_CORE_ERROR(...) 
	#define MH_CORE_FATAL(...) 
	// CORE Client
	#define MH_TRACE(...)
	#define MH_INFO(...)  
	#define MH_WARN(...)  
	#define MH_ERROR(...) 
	#define MH_FATAL(...) 

#endif // MH_LOG_SYSTEM

namespace CORE
{
	inline void Init() { MH_CORE_TRACE(MH_ENGINE, MH_VERSION); } // Log Singleton init in first use
	inline void Stop() { MH_CORE_TRACE("Shutdown MHelmet Engine"); CLOSE__LOG; }
}


#define MH_EXPAND_VARGS(x) x
#ifdef MH_ASSERT_SYSTEM
	
	#define MH_ASSERT_NO_MESSAGE(condition)   { if(!(condition)) { MH_ERROR("Assertion Failed"); __debugbreak(); } }
	#define MH_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { MH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

	#define MH_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
	#define MH_GET_ASSERT_MACRO(...) MH_EXPAND_VARGS(MH_ASSERT_RESOLVE(__VA_ARGS__, MH_ASSERT_MESSAGE, MH_ASSERT_NO_MESSAGE))

	#define MH_ASSERT(...) MH_EXPAND_VARGS( MH_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
	#define MH_CORE_ASSERT(...) MH_EXPAND_VARGS( MH_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
	#define MH_ASSERT(...)
	#define MH_CORE_ASSERT(...)
#endif

#ifdef MH_ENABLE_VERIFY
	#define MH_VERIFY_NO_MESSAGE(condition)   { if(!(condition)) { MH_ERROR("Verify Failed"); __debugbreak(); } }
	#define MH_VERIFY_MESSAGE(condition, ...) { if(!(condition)) { MH_ERROR("Verify Failed: {0}", __VA_ARGS__); __debugbreak(); } }

	#define MH_VERIFY_RESOLVE(arg1, arg2, macro, ...) macro
	#define MH_GET_VERIFY_MACRO(...) MH_EXPAND_VARGS(MH_VERIFY_RESOLVE(__VA_ARGS__, MH_VERIFY_MESSAGE, MH_VERIFY_NO_MESSAGE))

	#define MH_VERIFY(...) MH_EXPAND_VARGS( MH_GET_VERIFY_MACRO(__VA_ARGS__)(__VA_ARGS__) )
	#define MH_CORE_VERIFY(...) MH_EXPAND_VARGS( MH_GET_VERIFY_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
	#define MH_VERIFY(...)
	#define MH_CORE_VERIFY(...)
#endif
// Function Pointer to Event base class
#define CALLBACK std::function<void(Event&)>
// Perform Event Tasks
#define BIND(x) std::bind(&Engine::x, this, std::placeholders::_1)



