#pragma once
#include <MHpch.h>
#include "engine/baseWindow.hpp"

namespace MHelmet 
{

	class Engine {

	public:

		Engine();
		virtual ~Engine();

		void run();	
		
	private:
		bool _alive = true;
	};
	
	std::unique_ptr<Engine> createApp(); // definido en cliente
}


