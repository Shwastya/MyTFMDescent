#pragma once
#include "engine/MHCore.hpp"
#include "engine/platform/Window.hpp"
#include "engine/events/AppEvents/OnAppEvents.hpp"

namespace MHelmet 
{

	class Engine {

	public:

		Engine();
		virtual ~Engine();

		void run();


		void OnEvent(Event& event);
		
	private: /// Private Methods
		bool WindowCloseTask(OnWindowClose& e); // perform event

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Alive = true;
		
	};
	
	std::unique_ptr<Engine> createApp(); // definido en cliente
}


