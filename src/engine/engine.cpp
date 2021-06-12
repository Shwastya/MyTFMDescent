#include "engine/Engine.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "glm/glm.hpp"
#include "engine/system/Input.hpp"
#include "engine/system/geometry/triangle.hpp"
#include "engine/system/renderer/BufferLayout.hpp"

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

		

		Triangle T;

		//m_VBO = VBO::Create(T.Positions(), T.Size());

		m_VAO = VAO::Create();

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		
		m_VBO = VBO::Create(vertices, sizeof(vertices));
		Layout layout =
		{
			{ DataType::Float3, "aPos"},
			{ DataType::Float4, "aColor"}			
		};
		m_VBO->SetLayout(layout);
		m_VAO->Add__VBO(m_VBO);

		uint32_t indices[3] = { 0, 1, 2 };

		m_EBO = EBO::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VAO->Add__EBO(m_EBO);

		m_Shader.reset(new Shader(
			"../assets/shaders/basic/vertex.vs", 
			"../assets/shaders/basic/fragment.fs")
		);

		m_Shader->Use();
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
			m_VAO->Bind();
			//glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_EBO->Count(), GL_UNSIGNED_INT, nullptr);

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

