#pragma once
#include "../src/engine/mhpch.cpp"
#include "engine/system/platform/Window.hpp"
#include "engine/system/ImGui/ImGuiLayer.hpp"
//#include "engine/system/events/AppEvents/OnAppEvents.hpp"

#include <GLFW/glfw3.h>

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

		static float GetTime();

		
	private: 
		bool WindowCloseCallBack(OnWindowClose& event); // perform event
		bool WindowResizeCallBack(OnWindowResize& event);

	private:
		Unique<Window>	m_Window;
		
		bool m_Alive = true;
		bool m_Minimized = false;

		LayerManager  m_Layers;
		ImGuiLayer* m_ImGuiLayers;

		float m_LastFrame = 0.0f;
		DeltaTime m_DeltaTime;

	private:
		// necesito pasar el window al ImgUI Layer
		static Engine* s_Instance;
	};
	
	Unique<Engine> createApp(); // definido en cliente
}


