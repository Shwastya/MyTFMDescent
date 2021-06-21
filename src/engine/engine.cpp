#include "engine/system/MHCore.hpp"
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
		
		m_Window->SetVSync(true);
		m_Window->SetCallBack(BIND_E_FN(Engine::OnEvent));

		Renderer::Init();

		m_ImGuiLayers = new ImGuiLayer();
		PushOverlay(m_ImGuiLayers);	
		
	}

	Engine::~Engine() 
	{
		for (NodeLayer* layer : m_Layers)
		{			
			layer->Free();
			delete layer;
		}
	}		
	
	void Engine::run()								 
	{												 
		CORE_INFO("Mhelmet Engine running!");		

		while (m_Alive)								 
		{
			if (!m_Minimized)
			{
				for (NodeLayer* layer : m_Layers) layer->Update(m_DeltaTime);
			}
			

			m_ImGuiLayers->Begin();
			{
				for (NodeLayer* layer : m_Layers) layer->ImGuiRender();
			}			
			m_ImGuiLayers->End();



			m_Window->SwapBuffers();				
		
			float time = static_cast<float>(glfwGetTime());
			m_DeltaTime = time - m_LastFrame;
			m_LastFrame = time;						
		}											 
	}								


	void Engine::OnEvent(Event& e)
	{
		EventHandler handle(e);

		handle.CallBack <OnWindowClose  > (BIND_E_FN( Engine::WindowCloseCallBack  ));
		handle.CallBack <OnWindowResize > (BIND_E_FN( Engine::WindowResizeCallBack ));


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

	float Engine::GetTime() // for only used in main loop
	{
		 return static_cast<float>(glfwGetTime()); 
	}

	bool Engine::WindowCloseCallBack(OnWindowClose& e)
	{
		m_Alive = false;
		return true;
	}
	bool Engine::WindowResizeCallBack(OnWindowResize& e)
	{
		int width = e.GetWidth(), height = e.GetHeight();
	
		if (width == 0 || height == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		RenderDrawCall::SetWiewPort(0, 0, width, height);
		
		return false;
	}
}

