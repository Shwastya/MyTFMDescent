#include "engine/system/MHCore.hpp"
#include "engine/Engine.hpp"
#include "engine/system/renderer/BufferLayout.hpp"
#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/events/AppEvents/OnAppEvents.hpp"

namespace MHelmet 
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine(const std::string& name)
	{
		s_Instance = this;
		m_Window = Window::Create(WindowSpec(name));
		
		m_Window->SetVSync(true);	

		// Bindeamos las callbacks a la funcion miembro OnEvent()
		m_Window->SetCallBack(std::bind(&Engine::OnEvent, this, std::placeholders::_1));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);	

		CORE_INFO("Mhelmet Engine running!");		
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
		while (m_Alive)
		{
			if (!m_Minimized)
			for (NodeLayer* layer : m_Layers) layer->Update(m_TimeStep);

			m_ImGuiLayer->Begin();
			for (NodeLayer* layer : m_Layers) layer->ImGuiRender();			
			m_ImGuiLayer->End();

			m_Window->SwapBuffers();


			float time = GetTime();
			m_TimeStep = time - m_LastFrame;
			m_LastFrame = time;
		}											 
	}								


	void Engine::OnEvent(Event& e)
	{	

		if (e.GetEventType() == IsType::MH_WINDOW_CLOSE)
		{
			OnWindowClose& event = dynamic_cast<OnWindowClose&>(e);
			WindowCloseCallBack(event);
		}

		if (e.GetEventType() == IsType::MH_WINDOW_RESIZE)
		{
			OnWindowResize& event = dynamic_cast<OnWindowResize&>(e);
			WindowResizeCallBack(event);
		}	
		
		for (auto it = m_Layers.end(); it != m_Layers.begin();) 
			(*--it)->OnEvent(e); 
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
		const float getTime = static_cast<float>(glfwGetTime());

		return getTime;
		 //return static_cast<float>(glfwGetTime()); 
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

