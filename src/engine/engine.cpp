#include "engine/Engine.hpp"

#include "engine/system/renderer/BufferLayout.hpp"
#include "engine/system/renderer/Renderer.hpp"




namespace MHelmet 
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());		
		m_Window->SetCallBack(BindEventFunction(Engine::OnEvent));

		m_ImGuiLayers = new ImGuiLayer();
		PushOverlay(m_ImGuiLayers);				
	}

	Engine::~Engine() {}	

	
	///////////////////////////////////////////////////
	//				  ENGINE LOOP					 //
	///////////////////////////////////////////////////
	void Engine::run()								 
	{												 
		MH_CORE_INFO("Mhelmet Engine running!");	

	

		while (m_Alive)								 
		{
			

			for (NodeLayer* layer : m_Layers) layer->Update(m_DeltaTime);

			m_ImGuiLayers->Begin();
			for (NodeLayer* layer : m_Layers) layer->ImGuiRender();
			m_ImGuiLayers->End();


			m_Window->SwapBuffers();		

			float time = GetTime();
			m_DeltaTime = time - m_LastFrame;
			m_LastFrame = time;

			MH_CORE_INFO("LastFrame {0}", m_DeltaTime.MilliSeconds());

			
		}											 
	}												 
	///////////////////////////////////////////////////


	void Engine::OnEvent(Event& e)
	{
		PerformEvent perform(e);
		perform.DoTask<OnWindowClose>(BindEventFunction(Engine::WindowCloseTask));

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

	inline float Engine::GetTime() const
	{
		 return (float)glfwGetTime(); 
	}

	bool Engine::WindowCloseTask(OnWindowClose& e)
	{
		m_Alive = false;
		return m_Alive;
	}
}

