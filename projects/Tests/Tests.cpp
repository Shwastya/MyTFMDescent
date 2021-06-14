#include <MHelmet.h>

/**************************************
*       Proyecto Cliente Layer        *
* *************************************/
class TestingLayer : public MHelmet::NodeLayer
{
public:

	using R =  MHelmet::Renderer;
	using RC = MHelmet::RenderCommand;

	TestingLayer() : MHelmet::NodeLayer("TestingLayer")
	{
		m_Camera = std::make_shared<PerspectiveCamera>(glm::vec3(0.0f, 0.0f, 3.0f));
		R::SetCameraScene(m_Camera);


		m_VAO.reset(MHelmet::VAO::Create());

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

		std::shared_ptr<MHelmet::VBO> VBO_ = std::make_shared<MHelmet::OpenGLVBO>(positions, sizeof(positions));
		VBO_->Create(positions, sizeof(positions));

		VBO_->SetLayout({ {MHelmet::BUFFER::DataType::Float3, "a_Pos"} });
		m_VAO->Add__VBO(VBO_);

		uint32_t indices[] =
		{
			0, 1, 2, 3 ,4,  5,		//front
			6, 7, 8, 9, 10, 11,		//right
			12, 13, 14, 15, 16, 17, //back
			18, 19, 20, 21, 22, 23, //left
			24, 25, 26, 27, 28, 29, //bottom
			30, 31, 32, 33, 34, 35  //top
		};


		std::shared_ptr<MHelmet::EBO> EBO_ = std::make_shared<MHelmet::OpenGLEBO>(indices, sizeof(indices) / sizeof(uint32_t));

		m_VAO->Add__EBO(EBO_);
		m_Shader = std::make_shared<MHelmet::Shader>(
			"../assets/shaders/perspectiveShaders/vertex.vs",
			"../assets/shaders/perspectiveShaders/fragment.fs"
			);

	}

	void Update() override
	{
		RC::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RC::clear();

		R::BeginScene();
		R::Submit(m_Shader, m_VAO); 
	}

	void ImGuiRender()
	{
		
	}



	void OnEvent(MHelmet::Event& event) override
	{
		
	}

private:
	std::shared_ptr<MHelmet::Shader>   m_Shader;
	std::shared_ptr<MHelmet::VAO>      m_VAO;

	std::shared_ptr<PerspectiveCamera> m_Camera;
};
/**************************************
*           Proyecto Cliente          *
* *************************************/
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

extern std::unique_ptr<MHelmet::Engine> MHelmet::createApp()
{
	return std::make_unique<ProjectTesting>();
}

int main(int argc, char** argv)
{


	CORE::Init();

	auto project = MHelmet::createApp();
	project->run();

	CORE::Stop();



	return 0;
}