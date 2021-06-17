#include <MHelmet.h>
#include "engine/system/geometry/quad.hpp"
#include "engine/system/geometry/triangle.hpp"
#include "engine/system/geometry/cube.hpp"
#define MH MHelmet

/*****************************************************************************
*							Layer Proyecto Cliente 					         /
* ***************************************************************************/
class TestingLayer : public MHelmet::NodeLayer
{
public:




	using R   = MH::Renderer;
	using RDC = MH::RenderDrawCall;
	

	TestingLayer() : MH::NodeLayer("TestingLayer")
	{
		/* MATERIALS */
		std::string MaterialShader = "../assets/shaders/perspectiveShaders/materialShader.glsl";
		std::string TextureShader = "../assets/shaders/perspectiveShaders/textureShader.glsl";
		
;

		/* TEXTURES */
		std::string  textBricks = "../assets/textures/bricks_albedo.png";
		std::string  textBlueBlocks = "../assets/textures/blue_blocks.jpg";
		std::string  textAlphaTree = "../assets/textures/tree.png";

		m_Camera = std::make_shared<MH::PerspectiveCamera>(glm::vec3(11.6f, 9.0f, 23.5f));

		MH::Quad Q(1.0f);
		MH::Triangle T;
		MH::Cube C(0.8F);

		m_VAO.reset(MH::VAO::Create());

		MH::RefCount<MH::VBO> VBO_;
		VBO_ = MH::VBO::Create(C.GetModel(), C.Size());

		VBO_->SetLayout
		({ 
			{MH::BUFFER::DataType::Float3, "a_Pos"     },
			{MH::BUFFER::DataType::Float2, "a_UVS"     },
			{MH::BUFFER::DataType::Float3, "a_Normals"     }
		});

		m_VAO->Add__VBO(VBO_);	

		MH::RefCount<MH::EBO> EBO_;
		EBO_ = std::make_shared<MH::OpenGLEBO>(C.Indices(), C.Count());

		m_VAO->Add__EBO(EBO_);

		
		m_ShaderMaterial = MH::Shader::Create(MaterialShader);

		m_ShaderTexture  = MH::Shader::Create(TextureShader);

		m_Texture   = MH::Texture2D::Create(textBricks, MH::Texture2D::Format::RGB);
		m_AlphaTree = MH::Texture2D::Create(textAlphaTree, MH::Texture2D::Format::RGBA);


		

		
	}

	void Update(MH::DeltaTime dt) override
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

	void OnEvent(MH::Event& event) override
	{
		if (event.GetEventType() == MH::EventType::E_MOUSE_MOVED)
		{			
		//	if (false)
			HandleMouse((MH::OnMouseMoved&)event);			
		}
		if (event.GetEventType() == MH::EventType::E_KEY_PRESSED)
		{			
			MH::OnKeyPressed& e = (MH::OnKeyPressed&)event;

			if (e.GetKeyCode() == MH_KEY_F11)
			{				
				MH::Engine::p().GetWindow().SetCaptureMode(true);				
			}
			if (e.GetKeyCode() == MH_KEY_F10)
			{
				MH::Engine::p().GetWindow().SetCaptureMode(false);
			}
		}
		if (event.GetEventType() == MH::EventType::E_MOUSE_SCROLLED)
		{
			MH::OnMouseScrolled& e = (MH::OnMouseScrolled&)event;
			m_Camera->HandleMouseScroll(e.GetYOffset());
		}
	}

private:

	void HandleInput(MH::DeltaTime dt)
	{
		if (MH::Input::IsKeyPressed(MH_KEY_S))
		{
			m_Camera->Backward(dt);
		}
		if (MH::Input::IsKeyPressed(MH_KEY_W))
		{
			m_Camera->Forward(dt);
		}
		if (MH::Input::IsKeyPressed(MH_KEY_A))
		{
			m_Camera->Left(dt);
		}
		if (MH::Input::IsKeyPressed(MH_KEY_D))
		{
			m_Camera->Right(dt);
		}
	}

	void HandleMouse(MH::OnMouseMoved& e)
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

	void handleScroll(MH::DeltaTime dt)
	{

	}

	

private:

	MH::RefCount<MH::Shader>   m_ShaderMaterial;
	MH::RefCount<MH::Shader>   m_ShaderTexture;
	MH::RefCount<MH::Shader>   m_TESTINGGLSL;
	MH::RefCount<MH::VAO>      m_VAO;
	MH::RefCount<MH::PerspectiveCamera> m_Camera;
	MH::RefCount<MH::Texture2D> m_Texture, m_AlphaTree;

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