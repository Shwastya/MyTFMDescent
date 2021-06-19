#include "MyTFMLayer1.hpp"
#define SHADER   std::reinterpret_pointer_cast<OpenGLShader>

MyTFMDescent::MyTFMDescent() : MH::NodeLayer("TestingLayer")
{
	/* TEXTURES */
	std::string  BricksAlbedo = "../assets/textures/bricks_albedo.png";
	std::string  textBlueBlocks = "../assets/textures/blue_blocks.jpg";
	std::string  textAlphaTree = "../assets/textures/tree.png";

	m_Camera = std::make_shared<MH::CameraMan>(glm::vec3(11.6f, 9.0f, 30.5f));
	m_Camera->Speed(10.0f);
//	m_Camera->_Mouse = false;

	//MH::Quad Q(1.0f);

	const float half = 1.0f / 2.0f;

	float cube[288] =
	{
		//front

		// Positions            // UVS          // Normals
		-half, -half, half,     0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
		 half, -half, half,     1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
		 half,  half, half,     1.0f, 1.0f,     0.0f, 0.0f, 1.0f,

		-half, -half, half,     0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
		 half,  half, half,     1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
		-half,  half, half,     0.0f, 1.0f,     0.0f, 0.0f, 1.0f,

		//right

		half, -half, half,     0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
		half, -half,-half,     1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
		half,  half,-half,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,

		half, -half, half,     0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
		half,  half,-half,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
		half,  half, half,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,

		//back

		half, -half, -half,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
	   -half, -half, -half,    1.0f, 0.0f,     0.0f, 0.0f, -1.0f,
	   -half,  half, -half,    1.0f, 1.0f,     0.0f, 0.0f, -1.0f,

		half, -half, -half,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
		-half, half, -half,    1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
		half,  half, -half,    0.0f, 1.0f,     0.0f, 0.0f, -1.0f,

		//left

		-half, -half, -half,   0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
		-half, -half,  half,   1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
		-half,  half,  half,   1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,

		-half, -half, -half,   0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
		-half,  half,  half,   1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
		-half,  half, -half,   0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,

		//bottom

		-half, -half, -half,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		 half, -half, -half,   1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		 half, -half,  half,   1.0f, 1.0f,     0.0f, -1.0f, 0.0f,

		-half, -half, -half,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		 half, -half,  half,   1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
		-half, -half,  half,   0.0f, 1.0f,     0.0f, -1.0f, 0.0f,

		//top

		-half, half,   half,   0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
		 half, half,   half,   1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
		 half, half,  -half,   1.0f, 1.0f,     0.0f, 1.0f, 0.0f,

		-half, half,   half,   0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
		 half, half,  -half,   1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
		-half, half,  -half,   0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
	};



	uint32_t indices[36] =
	{
		0,  1,  2,      3,  4,  5,  // front
		6,  7,  8,      9,  10, 11, // right
		12, 13, 14,     15, 16, 17, // back
		18, 19, 20,     21, 22, 23, // left
		24, 25, 26,     27, 28, 29, // bottom
		30, 31, 32,     33, 34, 35  // top
	};





	m_VAO.reset(MH::VAO::Create());

	MH::RefCount<MH::VBO> VBO_;
	VBO_ = MH::VBO::Create(cube, sizeof(cube));

	VBO_->SetLayout
	({
		{MH::BUFFER::DataType::Float3, "a_Pos"     },
		{MH::BUFFER::DataType::Float2, "a_UVS"     },
		{MH::BUFFER::DataType::Float3, "a_Normals" }
	});

	m_VAO->Add__VBO(VBO_);

	MH::RefCount<MH::EBO> EBO_;
	EBO_ = std::make_shared<MH::OpenGLEBO>(indices, sizeof(indices) / sizeof(uint32_t));

	m_VAO->Add__EBO(EBO_);


	m_S.Load("PhongTexture", "../shaders/3D/phongBlinnColor.glsl");

	m_Texture = MH::Texture2D::Create(BricksAlbedo, MH::Texture2D::Format::RGB);
	m_AlphaTree = MH::Texture2D::Create(textAlphaTree, MH::Texture2D::Format::RGBA);
}

void MyTFMDescent::Update(MH::DeltaTime dt) 
{
	// update
	m_Camera->Update(dt);


	// render
	RDC::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	RDC::clear();



	R::BeginScene(m_Camera->Get());
	{
		
		R::Bind(m_S.Get("PhongTexture"));

		R::NormalMat(m_S.Get("PhongTexture"));

		R::Uniform(m_S.Get("PhongTexture"), "u_objectColor", m_ModelColor);
		R::Uniform(m_S.Get("PhongTexture"), "u_lightColor", m_LightColor);

		R::Uniform(m_S.Get("PhongTexture"), "u_ambientStrength", 0.2f);
		R::Uniform(m_S.Get("PhongTexture"), "u_lightPos", m_LightPos);

		R::Uniform(m_S.Get("PhongTexture"), "u_viewPos", m_Camera->Get().GetPosition());
		R::Uniform(m_S.Get("PhongTexture"), "u_shininess", 32);
		R::Uniform(m_S.Get("PhongTexture"), "u_specularStrength", 0.7f);

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

		m_Model.Translate = glm::vec3(10.0f, 9.0f, 0.0f);
		m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Model.Scale = glm::vec3(10.0f, 10.0f, 10.0f);
		m_Model.Degrees = MH::Engine::GetTime() * glm::radians(20.0f);
	
		R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);

		R::Submit(m_S.Get("PhongTexture"), m_VAO);
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
	m_Camera->OnEvent(event);

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