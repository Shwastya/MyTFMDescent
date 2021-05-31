
#include "engine/engine.hpp"



#include <GLFW/glfw3.h>

namespace MHelmet 
{
	
	Engine::Engine()
	{
	
	}
	Engine::~Engine() {}	


	void Engine::run()
	{
		MHelmet::Log::GetCoreLogger()->info("[Engine]-> Is running now");
		
		while (_alive)
		{
			
		}
	}	
}

