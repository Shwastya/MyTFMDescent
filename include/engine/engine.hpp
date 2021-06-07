#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/platform/Window.hpp"
#include "engine/system/node/NodeLayer.hpp"

#include "engine/system/events/AppEvents/OnAppEvents.hpp"

namespace MHelmet 
{

	class Engine {

	public:

		Engine();
		virtual ~Engine();

		void run();


		void OnEvent(Event& event);

		void PushLayer(NodeLayer* layer);
		void PushOverlay(NodeLayer* layer);
		
	private: /// Private Methods
		bool WindowCloseTask(OnWindowClose& e); // perform event

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Alive = true;
		NodeManager m_Layers;
	};
	
	std::unique_ptr<Engine> createApp(); // definido en cliente
}


