#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/platform/Window.hpp"

#include "engine/system/ImGui/ImGuiLayer.hpp"

#include "engine/system/events/AppEvents/OnAppEvents.hpp"

namespace MHelmet 
{

	class Engine 
	{

	public:

		Engine();
		virtual ~Engine();

		void run();

		void OnEvent(Event& event);

		void PushLayer(NodeLayer* layer);
		void PushOverlay(NodeLayer* layer);

		/* para esto es singleton Engine */
		static Engine& p() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

		
	private: 
		bool WindowCloseTask(OnWindowClose& e); // perform event

	private:
		std::unique_ptr<Window>	m_Window;
		
		bool m_Alive = true;
		LayerManager  m_Layers;
		ImGuiLayer* m_ImGuiLayers;
		
	private:
		// necesito pasar el window al ImgUI Layer
		static Engine* s_Instance;
	};
	
	std::unique_ptr<Engine> createApp(); // definido en cliente
}


