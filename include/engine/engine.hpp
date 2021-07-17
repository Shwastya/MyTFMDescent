#pragma once


#include "engine/system/platform/Window.hpp"
#include "engine/system/ImGui/ImGuiLayer.hpp"
#include <GLFW/glfw3.h>

namespace MHelmet 
{
	struct OnWindowClose;
	struct OnWindowResize;

	class Engine 
	{
	public:

		Engine(const std::string& name = "MHelmetProject");
		virtual ~Engine();

		void run();

		void OnEvent(Event& event);

		void PushLayer(NodeLayer* layer);
		void PushOverlay(NodeLayer* layer);

		static Engine& p() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

		void Exit() { m_Alive = false; }	

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static float GetTime();
		
	private: 
		bool WindowCloseCallBack(OnWindowClose& event); 
		bool WindowResizeCallBack(OnWindowResize& event);

	private:
		Unique<Window>	m_Window;
		
		bool m_Alive = true;
		bool m_Minimized = false;

		LayerManager  m_Layers;
		ImGuiLayer* m_ImGuiLayer;

		float m_LastFrame = 0.0f;
		TimeStep m_TimeStep;

	private:		
		static Engine* s_Instance;
	};
}


