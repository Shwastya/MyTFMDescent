#include "MyTFMLayer1.hpp"
#define SHADER   std::reinterpret_pointer_cast<OpenGLShader>

MyTFMDescent::MyTFMDescent() : MH::NodeLayer("TestingLayer")
{
	/* TEXTURES */
	std::string  BricksAlbedo = "../assets/textures/bricks_albedo.png";
	std::string  textBlueBlocks = "../assets/textures/blue_blocks.jpg";
	std::string  textAlphaTree = "../assets/textures/tree.png";

	m_CameraMan = std::make_shared<MH::CameraMan>(glm::vec3(11.6f, 9.0f, 30.5f));
	m_CameraMan->Speed(10.0f);
//	m_Camera->_Mouse = false;

	MH::Cube C(1.0f);
	MH::Quad Q(1.0f);
	MH::Sphere S(0.5f, 50, 50);
	MH::Teapot Tea(20);
	MH::Triangle T;

	m_VAO.reset(MH::VAO::Create());

	MH::RefCount<MH::VBO> VBO_;
	VBO_ = MH::VBO::Create(T.Get(), T.SizeVBO());
	VBO_->SetLayout
	({
		{MH::BUFFER::DataType::Float3, "a_Pos"         },
		{MH::BUFFER::DataType::Float2, "a_UVS"         },
		{MH::BUFFER::DataType::Float3, "a_Normals"     },
		{MH::BUFFER::DataType::Float3, "a_Tangents"    },
		{MH::BUFFER::DataType::Float3, "a_BiTangents"  }
	});

	m_VAO->Add__VBO(VBO_);

	MH::RefCount<MH::EBO> EBO_;
	EBO_ = std::make_shared<MH::OpenGLEBO>(T.Indices(), T.SizeIndices());
	

	m_VAO->Add__EBO(EBO_);

	m_S.Load("PhongTexture", "../shaders/3D/COLOR/phong1.glsl");

	m_Texture = MH::Texture2D::Create(BricksAlbedo, MH::Texture2D::Format::RGB);
	m_AlphaTree = MH::Texture2D::Create(textAlphaTree, MH::Texture2D::Format::RGBA);
}

void MyTFMDescent::Update(MH::DeltaTime dt) 
{
	// update
	m_CameraMan->Update(dt);

	// render
	RDC::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	RDC::clear();


	R::BeginScene(m_CameraMan->Get());
	{
		R::Bind(m_S.Get("PhongTexture"));

		R::Color(m_S.Get("PhongTexture"), "u_objectColor", m_ModelColor);		

		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 16; ++j)
			{
				

				m_Model.Translate = glm::vec3((i * 1.5) * 1.0f, (j * 1.5) * 1.0f, 0.0f);
				m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
				m_Model.Scale = glm::vec3(1.0f, 1.0f, 1.0f);
				m_Model.Degrees = MH::Engine::GetTime() * glm::radians(20.0f);				

				R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);

				R::Submit(m_S.Get("PhongTexture"), m_VAO);				
			}
		}

		R::Bind(m_S.Get("PhongTexture"));

		m_Model.Translate = glm::vec3(10.0f, 9.0f, 0.0f);
		m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Model.Scale = glm::vec3(10.0f, 10.0f, 10.0f);
		m_Model.Degrees = MH::Engine::GetTime() * glm::radians(20.0f);
	
		R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);

		R::Submit(m_S.Get("PhongTexture"), m_VAO);
		R::UnBind(m_S.Get("PhongTexture"));
	}
}

void MyTFMDescent::ImGuiRender()
{
	ImGui::Begin("Settings"); // Inicia una ventana nueva 

	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_LightColor));

	ImGui::End();
}

void MyTFMDescent::OnEvent(MH::Event& event) 
{
	m_CameraMan->OnEvent(event);

	if (event.GetEventType() == MH::IsType::MH_KEY_PRESSED)
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
}