#pragma once
#include "engine/MHCore.hpp"
#include "engine/platform/Window.hpp"

namespace MHelmet 
{

	class Engine {

	public:

		Engine();
		virtual ~Engine();

		void run();	
		
	private:
		bool m_Running = true;
	};
	
	std::unique_ptr<Engine> createApp(); // definido en cliente
}


