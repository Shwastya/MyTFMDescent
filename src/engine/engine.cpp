#include "engine/Engine.hpp"
#include <GLFW/glfw3.h>
#include "engine/system/Input.hpp"

namespace MHelmet 
{
	Engine* Engine::s_Instance = nullptr;
	
	Engine::Engine()
	{
		MH_CORE_ASSERT(!s_Instance, "App exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());		
		m_Window->SetCallBack(BINDAPPEVENT(OnEvent));


		
	}
	Engine::~Engine() {}	

	
	///////////////////////////////////////////////////S
	//				  ENGINE LOOP					 //
	///////////////////////////////////////////////////
	void Engine::run()								 
	{												 
		MH_CORE_INFO("Engine is running!");			 
									
		//Input::IsKeyPressed(GLFW_KEY_TAB);

		while (m_Alive)								 
		{											 
			glClearColor(0.7f, 0.3f, 0.6f, 1.0f);	 
			glClear(GL_COLOR_BUFFER_BIT);	
			
			/*MH_CORE_TRACE("{0}, {1}",
				Input::getMousePos().x,
				Input::getMousePos().y);*/
			
			for (NodeLayer* layer : m_Layers)
			{
				layer->Update();				
			}
			m_Window->SwapBuffers();				 
		}											 
	}												 
	///////////////////////////////////////////////////


	void Engine::OnEvent(Event& e)
	{
		//auto ex = std::make_unique<Layer>;
		PerformEvent perform(e);
		perform.DoTask<OnWindowClose>(BINDAPPEVENT(WindowCloseTask));
		//MH_CORE_TRACE("{0}", e);
		

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}

	}

	void Engine::PushLayer(NodeLayer* layer)
	{
		//auto ex = std::make_unique<Layer>(layer);
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

