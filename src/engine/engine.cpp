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

		

		//Triangle T;

		//m_VBO = VBO::Create(T.Positions(), T.Size());
		
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

		m_Shader = std::make_shared<Shader>("../assets/shaders/basic/vertex.vs", "../assets/shaders/basic/fragment.fs");
		
		

	/******************************************/
	// testing new layout
		
		m_VAO_Test.reset(VAO::Create());

		float vTest[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,    //upper right triangle
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,   //lower left triangle

		};
		std::shared_ptr<VBO> VBO_Test = std::make_shared<OpenGLVBO>(vTest, sizeof(vTest));
		VBO_Test->Create(vTest, sizeof(vTest));

		VBO_Test->SetLayout({ {BUFFER::DataType::Float3, "aPos"} });
		m_VAO_Test->Add__VBO(VBO_Test);
			
		uint32_t indices_test[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<EBO> EBO_Test = std::make_shared<OpenGLEBO>(indices_test, sizeof(indices_test) / sizeof(uint32_t));

		m_VAO_Test->Add__EBO(EBO_Test);
		m_Shader_Test = std::make_shared<Shader>(
			"../assets/shaders/basic/vertex-2.vs",
			"../assets/shaders/basic/fragment-2.fs"
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

		using R = Renderer;
		using RC = RenderCommand;

		while (m_Alive)								 
		{											 
				
			//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT);
			RC::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RC::clear();
			
			R::BeginScene();
			{

			}
			
						
			//m_VAO_Test->Bind();
			m_Shader_Test->Bind();
			Renderer::Submit(m_VAO_Test);
			glDrawElements(GL_TRIANGLES, m_VAO_Test->GetEBO()->Count(), GL_UNSIGNED_INT, nullptr);


			m_VAO->Bind();
			m_Shader->Bind();			
			glDrawElements(GL_TRIANGLES, m_VAO->GetEBO()->Count(), GL_UNSIGNED_INT, nullptr);

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

