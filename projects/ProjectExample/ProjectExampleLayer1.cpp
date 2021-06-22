#include "ProjectExampleLayer1.hpp"


MyTFMDescent::MyTFMDescent()
    : MH::NodeLayer("TestingLayer"), m_CameraMan(glm::vec3(0.0f, 0.0f, 3.5f))
{
    m_CameraMan.Speed(10.0f);


    const std::string texture = "../assets/textures/bricks_albedo.png";
    m_Texture = MH::Texture2D::Create(texture, MH::Texture2D::Format::RGB);
}




void MyTFMDescent::Join()
{
    m_BoardTexture = MH::Texture2D::Create("../assets/textures/blue_blocks.jpg", MH::Texture2D::Format::RGB);
}

void MyTFMDescent::Free() { }

void MyTFMDescent::Update(MH::DeltaTime dt)
{
    // UPDATE
    {
        m_CameraMan.Update(dt);
    }


    // RENDER
    {
       
        RenderDrawCall::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderDrawCall::clear();

        const glm::vec3 pos1{ 0.0f, 0.0f, -0.1f };
        const glm::vec3 size{ 10.0f, 10.0f, 10.0f };
        GeometryRender::DrawSimpleTextureQuad(m_CameraMan.Get(), m_BoardTexture, pos1, size);

        const glm::vec3 pos2{ 1.0f, 0.0f, 0.0f };
        const glm::vec4 color{ 0.8f, 0.1f, 0.6f, 1.0f };
        GeometryRender::DrawSimpleColorQuad(m_CameraMan.Get(), color, pos2);

        const glm::vec3 pos3{ -1.0f, 0.0f, 0.0f };
        GeometryRender::DrawSimpleTextureQuad(m_CameraMan.Get(), m_Texture, pos3);



        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 size2 = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 rotate = glm::vec3(0.f, 0.3f, 0.5f);
        float degrees = MH::Engine::GetTime() * glm::radians(20.0f);
        GeometryRender::DrawCube(position, size2, rotate, degrees);

        //GeometryRender::BeginScene(m_CameraMan.Get(), m_LightPos);
        //{
        //	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        //	glm::vec3 size = glm::vec3(0.5f, 0.5f, 0.5f);
        //	glm::vec3 rotate = glm::vec3(0.f, 0.3f, 0.5f);

        //	
        //	GeometryRender::DrawTeapot(position, size, rotate, degrees);

        //	for (int i = 0; i < 20; ++i)
        //	{
        //		for (int j = 0; j < 16; ++j)
        //		{

        //			glm::vec3 position = glm::vec3((i * 1.5) * 1.0f, (j * 1.5) * 1.0f, -7.0f);

        //			GeometryRender::DrawCube(position, size, rotate, degrees);

        //		}
        //	}
        //}
        GeometryRender::EndScene();
    }

}

void MyTFMDescent::ImGuiRender()
{    
    ImGui::Begin("Testing Light Position"); // begin 1

    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_LightPos)); 
   
    ImGui::End(); // end 1

}

void MyTFMDescent::OnEvent(MH::Event& event)
{
    m_CameraMan.OnEvent(event);

    if (event.GetEventType() == MH::IsType::MH_KEY_PRESSED)
    {
        MH::OnKeyPressed& e = (MH::OnKeyPressed&)event;

        if (e.GetKeyCode() == MH_KEY_Q)
        {
            MH::Engine::p().GetWindow().SetCaptureMode(true);
        }
        if (e.GetKeyCode() == MH_KEY_E)
        {
            MH::Engine::p().GetWindow().SetCaptureMode(false);
        }
    }
}