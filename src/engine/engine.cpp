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

		// La sincronización vertical (VSync) ayuda a dar estabilidad al sincronizar la velocidad de los fotogramas
		// con la velocidad de actualización del monitor.
		// Activado, DeltaTime pasa de unos 0.xxx segundos a aproximadamente 6s en mi monitor
		m_Window->SetVSync(true);
		m_Window->SetCallBack(BIND_E_FN(Engine::OnEvent));

		Renderer::Init();

		m_ImGuiLayers = new ImGuiLayer();
		PushOverlay(m_ImGuiLayers);	
		
	}

	Engine::~Engine() {}	

	
	///////////////////////////////////////////////////
	//				  ENGINE LOOP					 //
	///////////////////////////////////////////////////
	void Engine::run()								 
	{												 
		CORE_INFO("Mhelmet Engine running!");		

		while (m_Alive)								 
		{
			for (NodeLayer* layer : m_Layers)
			{
				layer->Update(m_DeltaTime);
			}

			m_ImGuiLayers->Begin();
			for (NodeLayer* layer : m_Layers)
			{
				layer->ImGuiRender();
			}
			m_ImGuiLayers->End();


			m_Window->SwapBuffers();		

			
		
			float time = GetTime();
			m_DeltaTime = time - m_LastFrame;
			m_LastFrame = time;
			
		}											 
	}												 
	///////////////////////////////////////////////////


	void Engine::OnEvent(Event& e)
	{
		EventHandler handle(e);

		handle.CallBack<OnWindowClose>(BIND_E_FN(Engine::WindowCloseCallBack));
		handle.CallBack<OnWindowResize>(BIND_E_FN(Engine::WindowResizeCallBack));


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

	bool Engine::WindowCloseCallBack(OnWindowClose& e)
	{
		m_Alive = false;
		return true;
	}
	bool Engine::WindowResizeCallBack(OnWindowResize& e)
	{
		/*int width = e.GetWidth(), height = e.GetHeight();
		if (width == 0 || height == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		m_Window ->GetSwapChain().OnResize(width, height);

		auto& fbs = FramebufferPool::GetGlobal()->GetAll();
		for (auto& fb : fbs)
		{
			if (!fb->GetSpecification().NoResize)
				fb->Resize(width, height);
		}
		*/
		return false;
	}
}

