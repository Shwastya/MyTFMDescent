#include "engine/Engine.hpp"
//#include <glad/glad.h>
//#include "engine/system/renderer/Renderer.hpp"
#include <GLFW/glfw3.h>
//#include "glm/glm.hpp"


#include "engine/system/Input.hpp"
//#include "engine/system/geometry/triangle.hpp"
#include "engine/system/renderer/BufferLayout.hpp"

#include "engine/system/renderer/Renderer.hpp"

#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVBO.hpp";
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp";


#include "engine/system/renderer/OrthographicCamera.hpp"
#include "engine/system/renderer/PerspectiveCamera.hpp"

/*TEMPORAL*/
#include <glm/gtc/matrix_transform.hpp>
/**********/


namespace MHelmet 
{
	OrthograpicCamera camera(-2.0f, 2.0f, -2.0f, 2.0f);
	//PerspectiveCamera camera2();

	

	Engine* Engine::s_Instance = nullptr;

	Engine::Engine()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());		
		m_Window->SetCallBack(BINDAPPEVENT(OnEvent));

		m_ImGuiLayers = new ImGuiLayer();
		PushOverlay(m_ImGuiLayers);			

		

		//Triangle T;

		//m_VBO = VBO::Create(T.Positions(), T.Size());
		/*
		m_VAO.reset(VAO::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
				0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VBO> VBO_T;
		VBO_T.reset(VBO::Create(vertices, sizeof(vertices)));

		VBO_T->SetLayout
		({
			{ BUFFER::DataType::Float3, "aPos"},
			{ BUFFER::DataType::Float4, "aColor"}
			});

		m_VAO->Add__VBO(VBO_T);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<EBO> EBO_T;
		EBO_T.reset(EBO::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VAO->Add__EBO(EBO_T);		

		m_Shader = std::make_shared<Shader>
			(
				"../assets/shaders/orthographicShaders/vertex.vs",
				"../assets/shaders/orthographicShaders/fragment.fs");
		
		
		*/
	/******************************************/
	// testing new layout
		
		m_VAO_Test.reset(VAO::Create());
		const float half = 1 / 2.0f;
		float positions[] = { -half, -half, half,    //front
						  half, -half, half,
						  half, half, half,

						  -half, -half, half,
						  half, half, half,
						  -half, half, half,

						  half, -half, half,    //right
						  half, -half, -half,
						  half, half, -half,

						  half, -half, half,
						  half, half, -half,
						  half, half, half,

						  half, -half, -half,    //back
						  -half, -half, -half,
						  -half, half, -half,

						  half, -half, -half,
						  -half, half, -half,
						  half, half, -half,

						  -half, -half, -half,    //left
						  -half, -half, half,
						  -half, half, half,

						  -half, -half, -half,
						  -half, half, half,
						  -half, half, -half,

						  -half, -half, -half,    //bottom
						  half, -half, -half,
						  half, -half, half,

						  -half, -half, -half,
						  half, -half, half,
						  -half, -half, half,

						  -half, half, half,    //top
						  half, half, half,
						  half, half, -half,

						  -half, half, half,
						  half, half, -half,
						  -half, half, -half };
	
		std::shared_ptr<VBO> VBO_ = std::make_shared<OpenGLVBO>(positions, sizeof(positions));
		VBO_->Create(positions, sizeof(positions));

		VBO_->SetLayout({ {BUFFER::DataType::Float3, "a_Pos"} });
		m_VAO_Test->Add__VBO(VBO_);
			
		uint32_t indices[] = 
		{ 
			0, 1, 2, 3 ,4,  5,		//front
			6, 7, 8, 9, 10, 11,		//right
			12, 13, 14, 15, 16, 17, //back
			18, 19, 20, 21, 22, 23, //left
			24, 25, 26, 27, 28, 29, //bottom
			30, 31, 32, 33, 34, 35  //top
		}; 
		

		std::shared_ptr<EBO> EBO_ = std::make_shared<OpenGLEBO>(indices, sizeof(indices) / sizeof(uint32_t));

		m_VAO_Test->Add__EBO(EBO_);
		m_Shader_Test = std::make_shared<Shader>(
			"../assets/shaders/perspectiveShaders/vertex.vs",
			"../assets/shaders/perspectiveShaders/fragment.fs"
		);

		// AQUI EL DELTA TIME TEMPORAL
		Engine::p().GetWindow().GetDeltaTime();
		
	}

	Engine::~Engine() {}	

	
	///////////////////////////////////////////////////
	//				  ENGINE LOOP					 //
	///////////////////////////////////////////////////
	void Engine::run()								 
	{												 
		MH_CORE_INFO("Engine is running!");			 
									
		//Input::IsKeyPressed(GLFW_KEY_TAB);

		using R = Renderer;
		using RC = RenderCommand;

		while (m_Alive)								 
		{											 
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view  = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			const float w = static_cast<float>(Engine::p().GetWindow().GetWidth());
			const float h = static_cast<float>(Engine::p().GetWindow().GetHeight());

			const glm::mat4 proj = glm::perspective(glm::radians(45.0f), w / h, 0.1f, 100.0f);
			
			RC::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RC::clear();
			
			R::BeginScene();
			
				m_Shader_Test->Bind();
				m_Shader_Test->SetUniform("u_Model", model);
				m_Shader_Test->SetUniform("u_View",  view);
				m_Shader_Test->SetUniform("u_Proj",  proj);
				
				R::Submit(m_VAO_Test); // to draw calls

				/*m_Shader->Bind();
				m_Shader->SetUniform("u_View", camera.GetViewProjectionMatrix());
				R::Submit(m_VAO);*/
			

			

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

