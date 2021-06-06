
#include "engine/Engine.hpp"




#include <GLFW/glfw3.h>
#include <bitset>

namespace MHelmet 
{

	
	Engine::Engine()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		
		m_Window->SetCallBack(BIND(OnEvent));
		
	}
	Engine::~Engine() {}	

	
	///////////////////////////////////////////////////
	//				  ENGINE LOOP					 //
	///////////////////////////////////////////////////
	void Engine::run()								 //
	{												 //
		MH_CORE_INFO("Engine is running!");			 //
													 //
		while (m_Alive)								 //
		{											 //
			glClearColor(0.7f, 0.3f, 0.6f, 1.0f);	 //
			glClear(GL_COLOR_BUFFER_BIT);			 //
			m_Window->SwapBuffers();				 //
		}											 //
	}												 //
	///////////////////////////////////////////////////


	void Engine::OnEvent(Event& e)
	{
		PerformEvent perform(e);
		perform.DoTask<OnWindowClose>(BIND(WindowCloseTask));
		MH_CORE_TRACE("{0}", e);

	}

	bool Engine::WindowCloseTask(OnWindowClose& e)
	{
		m_Alive = false;
		return m_Alive;
	}


	


}

