#include "engine/Engine.hpp"
#include <GLFW/glfw3.h>

#include "engine/system/Input.hpp"
#include "engine/system/renderer/BufferLayout.hpp"

#include "engine/system/renderer/Renderer.hpp"




namespace MHelmet 
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());		
		m_Window->SetCallBack(BINDAPPEVENT(OnEvent));

		m_ImGuiLayers = new ImGuiLayer();
		PushOverlay(m_ImGuiLayers);				
	}

	Engine::~Engine() {}	

	
	///////////////////////////////////////////////////
	//				  ENGINE LOOP					 //
	///////////////////////////////////////////////////
	void Engine::run()								 
	{												 
		MH_CORE_INFO("Engine is running!");	

		while (m_Alive)								 
		{
			for (NodeLayer* layer : m_Layers) layer->Update();

			m_ImGuiLayers->Begin();
			for (NodeLayer* layer : m_Layers) layer->ImGuiRender();
			m_ImGuiLayers->End();


			m_Window->Update();				 
		}											 
	}												 
	///////////////////////////////////////////////////


	void Engine::OnEvent(Event& e)
	{
		PerformEvent perform(e);
		perform.DoTask<OnWindowClose>(BINDAPPEVENT(WindowCloseTask));		

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}		
	}

	void Engine::PushLayer(NodeLayer* layer)
	{
		m_Layers.PushLayer(layer);
		layer->Join();
	}

	void Engine::PushOverlay(NodeLayer* layer)
	{
		m_Layers.PushOverlay(layer);
		layer->Join();
	}

	bool Engine::WindowCloseTask(OnWindowClose& e)
	{
		m_Alive = false;
		return m_Alive;
	}
}

