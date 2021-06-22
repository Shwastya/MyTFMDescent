#include "MyTFMLayer1.hpp"


MyTFMDescent::MyTFMDescent() 
	: MH::NodeLayer("TestingLayer"), m_CameraMan(glm::vec3(0.0f, 0.0f, 13.5f))
{
	m_CameraMan.Speed(10.0f);	


    const std::string texture = "../assets/textures/bricks_albedo.png";
    m_Texture = MH::Texture2D::Create(texture, MH::Texture2D::Format::RGB);
}




void MyTFMDescent::Join()
{
    m_BoardTexture = MH::Texture2D::Create("../assets/textures/blue_blocks.jpg", MH::Texture2D::Format::RGB);

    MH::FBTextureProps fbspec;
    fbspec.W = MH::Engine::p().GetWindow().GetWidth();
    fbspec.H = MH::Engine::p().GetWindow().GetHeight();

    m_FrameBuffer = MH::FrameBuffer::Create(fbspec);
}

void MyTFMDescent::Free() { }

void MyTFMDescent::Update(MH::DeltaTime dt) 
{
	//********************
    //****** UPDATE     **
    //********************
    if (m_IsViewportOnFocus)	m_CameraMan.Update(dt);

    glm::vec2 viewport;

    if (m_IsActivedImGui)
    {
        m_FrameBuffer->Bind();
        viewport.x = (float)MH::Engine::p().GetWindow().GetWidth();
        viewport.y = (float)MH::Engine::p().GetWindow().GetHeight();
    }
    else viewport = m_ViewPortSize;
	
    //********************
	//****** RENDER     **
    //********************
	{
        

		RenderDrawCall::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderDrawCall::clear();

      /*  const glm::vec3 pos1{0.0f, 0.0f, -0.1f};
        const glm::vec3 size{ 10.0f, 10.0f, 10.0f };
        GeometryRender::DrawSimpleTextureQuad(m_CameraMan.Get(), m_BoardTexture, pos1, size);
       
        const glm::vec3 pos2{1.0f, 0.0f, 0.0f };
        const glm::vec4 color{ 0.8f, 0.1f, 0.6f, 1.0f };
        GeometryRender::DrawSimpleColorQuad(m_CameraMan.Get(), color, pos2);

        const glm::vec3 pos3{ -1.0f, 0.0f, 0.0f };
        GeometryRender::DrawSimpleTextureQuad(m_CameraMan.Get(), m_Texture, pos3);



        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 size2 = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 rotate = glm::vec3(0.f, 0.3f, 0.5f);
        float degrees = MH::Engine::GetTime() * glm::radians(20.0f);
        GeometryRender::DrawCube(position, size2, rotate, degrees);*/
		
		GeometryRender::BeginScene(m_CameraMan.Get(), m_LightPos, m_ViewPortSize);
		{
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 size = glm::vec3(0.5f, 0.5f, 0.5f);
			glm::vec3 rotate = glm::vec3(0.f, 0.3f, 0.5f);
            float degrees = MH::Engine::GetTime() * glm::radians(20.0f);
			
			GeometryRender::DrawTeapot(position, size, rotate, degrees);

			for (int i = 0; i < 20; ++i)
			{
				for (int j = 0; j < 16; ++j)
				{

					glm::vec3 position = glm::vec3((i * 1.5) * 1.0f, (j * 1.5) * 1.0f, -7.0f);

					GeometryRender::DrawCube(position, size, rotate, degrees);

				}
			}
		}
		GeometryRender::EndScene();
        if (m_IsActivedImGui)  m_FrameBuffer->Unbind();
	}
	
}

void MyTFMDescent::ImGuiRender()
{
    if (m_IsActivedImGui)
    {
        static bool docksOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &docksOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                //ImGui::MenuItem("Padding", NULL, &opt_padding);
                //ImGui::Separator();

                if (ImGui::MenuItem("Exit")) MH::Engine::p().Exit();



                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }

        /* Mis pruebas */
        ImGui::Begin("Settings"); // begin 1
        ImGui::Text("Texto de ejempo: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");
        ImGui::Text("Frames: ");



        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_LightPos)); // begin 2
       // uint32_t testTextID = m_Texture->GetTextureID();


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("ViewPort");

        /* FLAG */ // Si hay foco del mouse sobre el frame del window // no bloquees los eventos desde Event System     
        m_IsViewportOnFocus = ImGui::IsWindowHovered(); // onfocus no pirula, pero hovered si     ;
        /*-----*/
        
        /* FLAG */ // Si cambia el ViewPort del frameImGui donde esta la textura de la escena
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        if ((m_ViewPortSize.x != viewportPanelSize.x) || (m_ViewPortSize.y != viewportPanelSize.y))
        {
            const uint32_t x = static_cast<uint32_t>(viewportPanelSize.x);
            const uint32_t y = static_cast<uint32_t>(viewportPanelSize.y);

            m_ViewPortSize = { viewportPanelSize.x, viewportPanelSize.y };
        }
        /*-----*/


        uint32_t textureID = m_FrameBuffer->GetFBOTexture(); // FBO  
        ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y}, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End(); // end 1
        ImGui::PopStyleVar(); // pop -> PushStyleVar(ImGuiStyleVar_WindowPadding)
        ImGui::End(); // end 2    
        ImGui::End(); // end 2   
    }     
}

void MyTFMDescent::OnEvent(MH::Event& event) 
{
	if (m_CameraMouse && m_IsViewportOnFocus) m_CameraMan.OnEvent(event);

	if (event.GetEventType() == MH::IsType::MH_KEY_PRESSED)
	{
		MH::OnKeyPressed& e = (MH::OnKeyPressed&)event;

		if (e.GetKeyCode() == MH_KEY_Q)	MH::Engine::p().GetWindow().SetCaptureMode(true);		
		if (e.GetKeyCode() == MH_KEY_E)	MH::Engine::p().GetWindow().SetCaptureMode(false);		

        if (e.GetKeyCode() == MH_KEY_O)	m_IsActivedImGui = false;
        if (e.GetKeyCode() == MH_KEY_P)	m_IsActivedImGui = true;

        if (e.GetKeyCode() == MH_KEY_M) m_CameraMouse = true;
        if (e.GetKeyCode() == MH_KEY_N) m_CameraMouse = false;

	}
}