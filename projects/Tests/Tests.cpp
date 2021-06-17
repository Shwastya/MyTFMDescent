#include <MHelmet.h>
#include "engine/system/geometry/quad.hpp"
#include "engine/system/geometry/triangle.hpp"
#include "engine/system/geometry/cube.hpp"


/*****************************************************************************
*							Layer Proyecto Cliente 					         /
* ***************************************************************************/
class TestingLayer : public MHelmet::NodeLayer
{
public:

	using R  =  MHelmet::Renderer;
	using RDC =  MHelmet::RenderDrawCall;	

	TestingLayer() : MHelmet::NodeLayer("TestingLayer")
	{
		/* MATERIALS */
		std::string MaterialShader = "../assets/shaders/perspectiveShaders/materialShader.vs";
		std::string TextureShader = "../assets/shaders/perspectiveShaders/textureShader.vs";
		
;

		/* TEXTURES */
		std::string  textBricks = "../assets/textures/bricks_albedo.png";
		std::string  textBlueBlocks = "../assets/textures/blue_blocks.jpg";
		std::string  textAlphaTree = "../assets/textures/tree.png";

		m_Camera = std::make_shared<MHelmet::PerspectiveCamera>(glm::vec3(11.6f, 9.0f, 23.5f));

		MHelmet::Quad Q(1.0f);
		MHelmet::Triangle T;
		MHelmet::Cube C(0.8F);

		m_VAO.reset(MHelmet::VAO::Create());

		MHelmet::RefCount<MHelmet::VBO> VBO_			;
		VBO_ = MHelmet::VBO::Create(C.GetModel(), C.Size());

		VBO_->SetLayout
		({ 
			{MHelmet::BUFFER::DataType::Float3, "a_Pos"     },
			{MHelmet::BUFFER::DataType::Float2, "a_UVS"     },
			{MHelmet::BUFFER::DataType::Float3, "a_Normals"     }
		});

		m_VAO->Add__VBO(VBO_);	

		MHelmet::RefCount<MHelmet::EBO> EBO_;
		EBO_ = std::make_shared<MHelmet::OpenGLEBO>(C.Indices(), C.Count());

		m_VAO->Add__EBO(EBO_);

		
		m_ShaderMaterial = MHelmet::Shader::Create(MaterialShader);

		m_ShaderTexture = MHelmet::Shader::Create(TextureShader);

		m_Texture = MHelmet::Texture2D::Create(textBricks, MHelmet::Texture2D::Format::RGB);
		m_AlphaTree = MHelmet::Texture2D::Create(textAlphaTree, MHelmet::Texture2D::Format::RGBA);


		

		
	}

	void Update(MHelmet::DeltaTime dt) override
	{
		HandleInput(dt);		

		RDC::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RDC::clear();
		 
		R::BeginScene(m_Camera);
		{
			for (int i = 0; i < 20; ++i)
			{
				for (int j = 0; j < 16; ++j)
				{
					m_Model.Translate = glm::vec3((i * 1.5) * 1.0f, (j * 1.5) * 1.0f, 0.0f);
					m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
					m_Model.Scale = glm::vec3(1.0f, 1.0f, 1.0f);
			
					m_Model.Degrees = static_cast<float>(glfwGetTime()) * glm::radians(20.0f);
					
					m_Model.Degrees = 0.0f;

				//	m_Texture->Bind(0);
					R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);
					R::Material(m_ShaderMaterial, m_ModelColor);
					R::Submit(m_ShaderMaterial, m_VAO);
				}
			}

			m_Model.Translate = glm::vec3(10.0f, 9.0f, 0.0f);
			m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
			m_Model.Scale = glm::vec3(10.0f, 10.0f, 10.0f);
			m_Model.Degrees = static_cast<float>(glfwGetTime()) * glm::radians(20.0f);
			//m_Model.Degrees = static_cast<float>(glfwGetTime()) * glm::radians(20.0f);

			R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);
			R::Texture(m_ShaderTexture, m_Texture, 0);
			R::Submit(m_ShaderTexture, m_VAO);



			m_Model.Translate = glm::vec3(10.0f, 9.0f, 5.0f);
			m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
			m_Model.Scale = glm::vec3(10.0f, 10.0f, 10.0f);
			m_Model.Degrees = 0.0f;
			//m_Model.Degrees = static_cast<float>(glfwGetTime()) * glm::radians(20.0f);

			R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);
			R::Texture(m_ShaderTexture, m_AlphaTree, 0);
			R::Submit(m_ShaderTexture, m_VAO);
		}	
	}  

	void ImGuiRender()
	{
		ImGui::Begin("Settings"); // Inicia una ventana nueva 

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_ModelColor));

		ImGui::End();		
	}

	void OnEvent(MHelmet::Event& event) override
	{
		if (event.GetEventType() == MHelmet::EventType::E_MOUSE_MOVED)
		{			
		//	if (false)
			HandleMouse((MHelmet::OnMouseMoved&)event);			
		}
		if (event.GetEventType() == MHelmet::EventType::E_KEY_PRESSED)
		{			
			MHelmet::OnKeyPressed& e = (MHelmet::OnKeyPressed&)event;

			if (e.GetKeyCode() == MH_KEY_F11)
			{				
				MHelmet::Engine::p().GetWindow().SetCaptureMode(true);				
			}
			if (e.GetKeyCode() == MH_KEY_F10)
			{
				MHelmet::Engine::p().GetWindow().SetCaptureMode(false);
			}
		}
		if (event.GetEventType() == MHelmet::EventType::E_MOUSE_SCROLLED)
		{
			MHelmet::OnMouseScrolled& e = (MHelmet::OnMouseScrolled&)event;
			m_Camera->HandleMouseScroll(e.GetYOffset());
		}
	}

private:

	void HandleInput(MHelmet::DeltaTime dt)
	{
		if (MHelmet::Input::IsKeyPressed(MH_KEY_S))
		{
			m_Camera->Backward(dt);
		}
		if (MHelmet::Input::IsKeyPressed(MH_KEY_W))
		{
			m_Camera->Forward(dt);
		}
		if (MHelmet::Input::IsKeyPressed(MH_KEY_A))
		{
			m_Camera->Left(dt);
		}
		if (MHelmet::Input::IsKeyPressed(MH_KEY_D))
		{
			m_Camera->Right(dt);
		}
	}

	void HandleMouse(MHelmet::OnMouseMoved& e)
	{		
		if (m_FirstMouse)
		{
			m_FirstMouse = false;
			m_LastX = e.GetX();
			m_LastY = e.GetY();
		}

		const float Xoffset = e.GetX() - m_LastX;
		const float Yoffset = m_LastY - e.GetY();
		m_LastX = e.GetX();
		m_LastY = e.GetY();

		m_Camera->HandleMouseMovement(Xoffset, Yoffset);
	}

	void handleScroll(MHelmet::DeltaTime dt)
	{

	}

	

private:
	MHelmet::RefCount<MHelmet::Shader>   m_ShaderMaterial;
	MHelmet::RefCount<MHelmet::Shader>   m_ShaderTexture;

	MHelmet::RefCount<MHelmet::Shader>   m_TESTINGGLSL;

	MHelmet::RefCount<MHelmet::VAO>      m_VAO;

	MHelmet::RefCount<MHelmet::PerspectiveCamera> m_Camera;

	MHelmet::RefCount<MHelmet::Texture2D> m_Texture, m_AlphaTree;

	/* atributos para los modelos */
	
	ModelTransform m_Model;
	glm::vec3 m_ModelColor{ 1.0f, 0.0f, 0.5f };


	/* atributos para el mouse e interfaz */
	bool m_FirstMouse = true;
	float m_LastX = 0.0f;
	float m_LastY = 0.0f;
	bool toggle = true;
};


/*****************************************************************************
*							    Proyecto Cliente					         /
* ***************************************************************************/
class ProjectTesting : public MHelmet::Engine {

public:
	ProjectTesting()
	{
		PushLayer(new TestingLayer());
	}

	~ProjectTesting()
	{
	}
};

extern MHelmet::Unique<MHelmet::Engine> MHelmet::createApp()
{
	return std::make_unique<ProjectTesting>();
}


/*****************************************************************************
*							      main program		   			             /
* ***************************************************************************/
int main(int argc, char** argv)
{
	CORE::Init();

	auto project = MHelmet::createApp();
	project->run();

	CORE::Stop();

	return 0;
}