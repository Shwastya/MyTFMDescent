#include "MyTFMLayer1.hpp"

#define W static_cast<float>(Engine::p().GetWindow().GetWidth())
#define H static_cast<float>(Engine::p().GetWindow().GetHeight())

MyTFMDescent::MyTFMDescent() : NodeLayer("TestingLayer") {}

void MyTFMDescent::Join()
{
    // Framebuffer instancia y texture specs
    FBTextureProps fbspec{ Engine::p().GetWindow().GetWidth(), Engine::p().GetWindow().GetHeight() };
    m_FrameBuffer = FrameBuffer::Create(fbspec);

    // Create scene ECS   
    m_Scene = std::make_shared<Scene>();

    // ENTITIES

    // CameraMans
    Ent_CameraMan1 = m_Scene->CreateEntity("Camera 1");
    Ent_CameraMan1.AddComponent<CameraManComponent>(glm::vec3(0.0f, 1.0f, 15.5f), W, H);

    Ent_CameraMan2 = m_Scene->CreateEntity("Camera 2");
    Ent_CameraMan2.AddComponent<CameraManComponent>(glm::vec3(0.0f, 1.0f, 15.5f), W, H);
    Ent_CameraMan2.GetComponent<CameraManComponent>().Primary = false;

    // Light
    Ent_Light = m_Scene->CreateEntity("Light Reference");
    Ent_Light.AddComponent<LightComponent>();
    Ent_Light.AddComponent<MaterialComponent>();
    Ent_Light.GetComponent<TransformComponent>().T = Ent_Light.GetComponent<LightComponent>().Position;
    Ent_Light.GetComponent<TransformComponent>().S = glm::vec3(0.5f, 0.5f, 0.5f);
    

    
    // cube
    Ent_Cube = m_Scene->CreateEntity("Cube");
    Ent_Cube.AddComponent<MaterialComponent>();
    Ent_Cube.GetComponent<TransformComponent>().ID = 1;


    // teapot
    Ent_TeaPot = m_Scene->CreateEntity("Tea Pot");
    Ent_TeaPot.AddComponent<MaterialComponent>();
    Ent_TeaPot.GetComponent<TransformComponent>().ID = 2;
    Ent_TeaPot.GetComponent<TransformComponent>().T = glm::vec3(-1.0f, 1.0f, -5.0f);
    Ent_TeaPot.GetComponent<TransformComponent>().R = glm::vec3(1.0f, 0.0f, 0.0f);
    Ent_TeaPot.GetComponent<TransformComponent>().S = glm::vec3(0.5f, 0.5f, 0.5f);

  

    

    // le damos el con
    m_HierarchyPanel.SetContext(m_Scene);
}

void MyTFMDescent::Free() { }

void MyTFMDescent::Update(DeltaTime dt) 
{ 
    m_FrameBuffer->Bind();
    {
        RenderDrawCall::ClearColor({ 0.1f, 0.1f, 1.0f, 1.0f });
        RenderDrawCall::clear();

        m_Scene->Update(dt);
    }
    m_FrameBuffer->Unbind();	
}

void MyTFMDescent::ImGuiRender()
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

            if (ImGui::MenuItem("Exit")) Engine::p().Exit();



            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    /*************************************/
    m_HierarchyPanel.OnImGuiRender();
    /*************************************/
    

    /* My ImGui SETTINGS */ 
    ImGui::Begin("Specifications:"); // begin 1
    ImGui::NewLine();
    ImGui::Text("GPU:      NVIDIA Corporation");
    ImGui::Text("Renderer: NVIDIA GeForce RTX 2080 Ti/PCIe/SSE2");
    ImGui::Text("Version:  N4.6.0 NVIDIA 466.77");
    ImGui::NewLine(); 
    ImGui::Separator();
    ImGui::NewLine();
    ImGui::Text("Active camera");
    // checkbox
    if (ImGui::Checkbox("Editor Camera", &m_PrimaryCam))
    {
        Ent_CameraMan2.GetComponent<CameraManComponent>().Primary = !m_PrimaryCam;
        Ent_CameraMan1.GetComponent<CameraManComponent>().Primary =  m_PrimaryCam;
    }
  
    /* SCENE FRAME */
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Scene Frame");

    /* FLAG */ // Si cambia el ViewPort del frameImGui donde esta la textura de la escena
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();    
    {
        /* FLAG */ // Si hay foco del mouse sobre el frame del window // no bloquees los eventos desde Event System
        Ent_CameraMan1.GetComponent<CameraManComponent>().IsHovered = ImGui::IsWindowHovered();        

        const float X = Ent_CameraMan1.GetComponent<CameraManComponent>().ViewportX;
        const float Y = Ent_CameraMan1.GetComponent<CameraManComponent>().ViewportY;

        if ((X != viewportPanelSize.x) || (Y != viewportPanelSize.y))
        {
            Ent_CameraMan1.GetComponent<CameraManComponent>().ViewportX = viewportPanelSize.x;
            Ent_CameraMan1.GetComponent<CameraManComponent>().ViewportY = viewportPanelSize.y;
        }
    }   
    {        
        const float X2 = Ent_CameraMan2.GetComponent<CameraManComponent>().ViewportX;
        const float Y2 = Ent_CameraMan2.GetComponent<CameraManComponent>().ViewportY;

        if ((X2 != viewportPanelSize.x) || (Y2 != viewportPanelSize.y))
        {
            Ent_CameraMan2.GetComponent<CameraManComponent>().ViewportX = viewportPanelSize.x;
            Ent_CameraMan2.GetComponent<CameraManComponent>().ViewportY = viewportPanelSize.y;
        }
    }     

    uint32_t textureID = m_FrameBuffer->GetFBOTexture(); // FBO  
    ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y}, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

    ImGui::End(); // end 1
    ImGui::PopStyleVar(); // pop -> PushStyleVar(ImGuiStyleVar_WindowPadding)
    ImGui::End(); // end 2    
    ImGui::End(); // end 2   

    //static bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);
     
}

void MyTFMDescent::OnEvent(Event& event) 
{
	
    if (Ent_CameraMan1)
    {
        if (Ent_CameraMan1.GetComponent<CameraManComponent>().Primary)
        {
            auto& cam = Ent_CameraMan1.GetComponent<CameraManComponent>();

            if (m_Editor_Cam_FirtsUse)
            {
                m_Editor_Cam_FirtsUse = false;
                cam.Cameraman._Mouse = false;
            }

            if (cam.IsHovered)
            {
                if (event.GetEventType() == IsType::MH_MOUSE_BUTTON_PRESSED)
                    cam.Cameraman._Mouse = true;

                if (event.GetEventType() == IsType::MH_MOUSE_BUTTON_RELEASED)
                    cam.Cameraman._Mouse = false;

                cam.Cameraman.OnEvent(event);
            }
        }
    }
    if (Ent_CameraMan2)
    {
        if (Ent_CameraMan2.GetComponent<CameraManComponent>().Primary)
        {
            auto& cam = Ent_CameraMan2.GetComponent<CameraManComponent>();
            if (cam.IsHovered) cam.Cameraman.OnEvent(event);
        }
    }

	if (event.GetEventType() == IsType::MH_KEY_PRESSED)
	{
		OnKeyPressed& e = (OnKeyPressed&)event;

		if (e.GetKeyCode() == MH_KEY_Q)	Engine::p().GetWindow().SetCaptureMode(true);		
		if (e.GetKeyCode() == MH_KEY_E)	Engine::p().GetWindow().SetCaptureMode(false);		

        if (e.GetKeyCode() == MH_KEY_O)	m_IsActivedImGui = false;
        if (e.GetKeyCode() == MH_KEY_P)	m_IsActivedImGui = true;
	}
}
