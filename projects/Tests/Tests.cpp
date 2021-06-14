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
		//R::InitCameraScene(glm::vec3(0.0f, 0.0f, 3.0f));


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

		HandleInput();

		RC::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RC::clear();

		R::BeginScene(m_Camera);
		R::Submit(m_Shader, m_VAO); 
	}

	void ImGuiRender()
	{
		
	}



	void OnEvent(MHelmet::Event& event) override
	{
		if (event.GetEventType() == MHelmet::EventType::E_MOUSE_MOVED)
		{			
			
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

	void HandleInput()
	{
		const float dt = MHelmet::Engine::p().GetWindow().GetDeltaTime();

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

	void handleScroll(float dt)
	{

	}


private:
	std::shared_ptr<MHelmet::Shader>   m_Shader;
	std::shared_ptr<MHelmet::VAO>      m_VAO;

	std::shared_ptr<PerspectiveCamera> m_Camera;

	/* atributos para el mouse e interfaz */
	bool m_FirstMouse = true;
	float m_LastX = 0.0f;
	float m_LastY = 0.0f;
	bool toggle = true;


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