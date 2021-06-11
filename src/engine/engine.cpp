#include "engine/Engine.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "glm/glm.hpp"
#include "engine/system/Input.hpp"
#include "engine/system/geometry/triangle.hpp"

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

		// vertex array object   VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		// vertex buffer oobject VBO
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		Triangle tri;	
		
		glBufferData(GL_ARRAY_BUFFER, tri.SizePos(), tri.Positions(), GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// index  buffer object  EBO
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.SizeInd(), tri.Indices(), GL_STATIC_DRAW);

		// no es necesario hacer unique ptr
		// la clase shader es basicamente un monton 
		// de funciones con solo el atributo del id
		// y podemos ahorrarnos hacer un allocate

		m_Shader.reset(new Shader(
			"../assets/shaders/basic/vertex.vs", 
			"../assets/shaders/basic/fragment.fs")
		);
	}


	Engine::~Engine() {}	

	
	///////////////////////////////////////////////////
	//				  ENGINE LOOP					 //
	///////////////////////////////////////////////////
	void Engine::run()								 
	{												 
		MH_CORE_INFO("Engine is running!");			 
									
		//Input::IsKeyPressed(GLFW_KEY_TAB);

		while (m_Alive)								 
		{											 
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);	 
			glClear(GL_COLOR_BUFFER_BIT);	
			
			m_Shader->Use();

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

