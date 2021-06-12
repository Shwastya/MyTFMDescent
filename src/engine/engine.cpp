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

	/* pasado a VAO Opengl*/
	static GLenum ToOpenGLBaseType(DataType type)
	{
		switch (type)
		{		  
		case MHelmet::DataType::Float:  return GL_FLOAT;
		case MHelmet::DataType::Float2: return GL_FLOAT;
		case MHelmet::DataType::Float3:	return GL_FLOAT;
		case MHelmet::DataType::Float4:	return GL_FLOAT;
		case MHelmet::DataType::Int:	return GL_INT;
		case MHelmet::DataType::Int2:	return GL_INT;
		case MHelmet::DataType::Int3:	return GL_INT;
		case MHelmet::DataType::Int4:	return GL_INT;
		case MHelmet::DataType::Mat3:	return GL_FLOAT;
		case MHelmet::DataType::Mat4:	return GL_FLOAT;
		case MHelmet::DataType::Bool:	return GL_BOOL;
		}
		return 0;
	}
	/**********************/
	Engine::Engine()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());		
		m_Window->SetCallBack(BINDAPPEVENT(OnEvent));

		m_ImGuiLayers = new ImGuiLayer();
		PushOverlay(m_ImGuiLayers);			

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		Triangle T;

		//m_VBO = VBO::Create(T.Positions(), T.Size());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		
		m_VBO2 = VBO::Create(vertices, sizeof(vertices));

		Layout layout =
		{
			{ DataType::Float3, "aPos"},
			{ DataType::Float4, "aColor"},
			{ DataType::Float4, "aColor"}
		};

		std::cout 
			<<
			"Numero de elementos: " <<
			layout.GetNumberOfElements() 
			<< std::endl;

		/* pasado a VAO Opengl*/
		uint32_t idx = 0;
		for (const auto& e : layout)
		{
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer
			(
				idx, 
				e.ComponentCount(), 
				ToOpenGLBaseType(e.Type), 
				e.Normalized ? GL_TRUE : GL_FALSE, 
				layout.Stride(),
				(const void*)e.Offset
			);
			++idx;
		}
		/************************/

		uint32_t indices[3] = { 0, 1, 2 };

		m_EBO = EBO::Create(indices, sizeof(indices) / sizeof(uint32_t));

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

			glBindVertexArray(m_VAO);
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

