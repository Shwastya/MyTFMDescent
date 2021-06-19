#include <MHelmet.h>
#include "MyTFMDescentLayer.hpp"

#define MH MHelmet  // CLIENT SIDE

class MyTFMDescent : public MHelmet::NodeLayer
{

public:

	using R = MH::Renderer;
	using RDC = MH::RenderDrawCall;

	MyTFMDescent() : MH::NodeLayer("TestingLayer")
	{
		/* TEXTURES */
		std::string  textBricks = "../assets/textures/bricks_albedo.png";
		std::string  textBlueBlocks = "../assets/textures/blue_blocks.jpg";
		std::string  textAlphaTree = "../assets/textures/tree.png";

		m_Camera = std::make_shared<MH::CameraMan>(glm::vec3(11.6f, 9.0f, 30.5f));
		m_Camera->Speed(10.0f);
		m_Camera->_Mouse = false;

		//MH::Quad Q(1.0f);
	//	MH::Cube C(1.0f);
		//MH::Teapot T(20);
		//MH::Sphere Q(1.0f, 20, 20);


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
			{MH::BUFFER::DataType::Float3, "a_Normals"     }
			});

		m_VAO->Add__VBO(VBO_);

		MH::RefCount<MH::EBO> EBO_;
		EBO_ = std::make_shared<MH::OpenGLEBO>(indices, sizeof(indices) / sizeof(uint32_t));

		m_VAO->Add__EBO(EBO_);

		// Added Shader Library
		m_S.Load("OnlyColor", "../shaders/persp/colorShader.glsl");
		m_S.Load("OnlyTextU", "../shaders/persp/textuShader.glsl");

		m_Texture = MH::Texture2D::Create(textBricks, MH::Texture2D::Format::RGB);
		m_AlphaTree = MH::Texture2D::Create(textAlphaTree, MH::Texture2D::Format::RGBA);
	}

	void Update(MH::DeltaTime dt) override
	{
		// update
		m_Camera->Update(dt);

		print();
		// render
		RDC::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RDC::clear();

		R::BeginScene(m_Camera->Get());
		{
			for (int i = 0; i < 20; ++i)
			{
				for (int j = 0; j < 16; ++j)
				{
					m_Model.Translate = glm::vec3((i * 1.5) * 1.0f, (j * 1.5) * 1.0f, 0.0f);
					m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
					m_Model.Scale = glm::vec3(1.0f, 1.0f, 1.0f);

					// m_Model.Degrees = static_cast<float>(glfwGetTime()) * glm::radians(20.0f);

					m_Model.Degrees = MH::Engine::GetTime() * glm::radians(20.0f);

					//	m_Model.Degrees = 0.0f;

					//	m_Texture->Bind(0);
					R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);
					R::Material(m_S.Get("OnlyColor"), m_ModelColor);
					R::Submit(m_S.Get("OnlyColor"), m_VAO);
				}
			}

			m_Model.Translate = glm::vec3(10.0f, 9.0f, 0.0f);
			m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
			m_Model.Scale = glm::vec3(10.0f, 10.0f, 10.0f);
			m_Model.Degrees = MH::Engine::GetTime() * glm::radians(20.0f);
			//m_Model.Degrees = static_cast<float>(glfwGetTime()) * glm::radians(20.0f);

			R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);
			R::Texture(m_S.Get("OnlyTextU"), m_Texture, 0);
			R::Submit(m_S.Get("OnlyTextU"), m_VAO);



			m_Model.Translate = glm::vec3(10.0f, 9.0f, 5.0f);
			m_Model.Rotate = glm::vec3(1.0f, 1.0f, 1.0f);
			m_Model.Scale = glm::vec3(10.0f, 10.0f, 10.0f);
			m_Model.Degrees = 0.0f;
			//m_Model.Degrees = static_cast<float>(glfwGetTime()) * glm::radians(20.0f);

			R::Model(m_Model.Translate, m_Model.Rotate, m_Model.Scale, m_Model.Degrees);
			R::Texture(m_S.Get("OnlyTextU"), m_AlphaTree, 0);
			R::Submit(m_S.Get("OnlyTextU"), m_VAO);
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

private:

	MH::ShaderLib m_S; // Shader Library

	MH::RefCount<MH::VAO>       m_VAO;
	MH::RefCount<MH::CameraMan> m_Camera;
	MH::RefCount<MH::Texture2D> m_Texture, m_AlphaTree;

	/* atributos para los modelos */
	ModelTransform m_Model;
	glm::vec3 m_ModelColor{ 1.0f, 0.0f, 0.5f };

};


/*****************************************************************************
*							    Proyecto Cliente					         /
* ***************************************************************************/
class ProjectTesting : public MHelmet::Engine {

public:
	ProjectTesting()
	{
		PushLayer(new MyTFMDescent());
	}

	~ProjectTesting() { /* delete de layers responsabiliad del Engine */ }
};

MH::Unique<MH::Engine> MH::createApp() { return std::make_unique<ProjectTesting>(); }


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