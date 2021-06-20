#include "MyTFMLayer1.hpp"
#define SHADER   std::reinterpret_pointer_cast<OpenGLShader>

MyTFMDescent::MyTFMDescent() 
	: MH::NodeLayer("TestingLayer")
{
	/* TEXTURES */
	std::string  BricksAlbedo = "../assets/textures/bricks_albedo.png";
	std::string  textBlueBlocks = "../assets/textures/blue_blocks.jpg";
	std::string  textAlphaTree = "../assets/textures/tree.png";

	m_CameraMan = std::make_shared<MH::CameraMan>(glm::vec3(0.0f, 1.0f, 14.5f));
	m_CameraMan->Speed(10.0f);
//	m_Camera->_Mouse = false;

	

	m_Texture = MH::Texture2D::Create(BricksAlbedo, MH::Texture2D::Format::RGB);
	m_AlphaTree = MH::Texture2D::Create(textAlphaTree, MH::Texture2D::Format::RGBA);
}

void MyTFMDescent::Update(MH::DeltaTime dt) 
{
	// update
	m_CameraMan->Update(dt);

	// render
	RenderDrawCall::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	RenderDrawCall::clear();


	GeometryRender::BeginScene(m_CameraMan->Get(), m_LightPos, m_LightColor);
	{
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 size     = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 rotate = glm::vec3(0.f, 0.3f, 0.5f);

		float degrees = MH::Engine::GetTime() * glm::radians(20.0f);
		GeometryRender::DrawTeapot(position, m_ModelColor, size, rotate, degrees);

		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 16; ++j)
			{

				glm::vec3 position = glm::vec3((i * 1.5) * 1.0f, (j * 1.5) * 1.0f, -7.0f);

				GeometryRender::DrawCube(position, m_ModelColor, size, rotate, degrees);
			
			}
		}
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