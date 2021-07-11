#include "MyTFMLayer1.hpp"
#include <ImGuizmo.h>
#include "engine/system/scene/SerializerScene.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"


#define W_ static_cast<float>(Engine::p().GetWindow().GetWidth())
#define H_ static_cast<float>(Engine::p().GetWindow().GetHeight())

MyTFMDescent::MyTFMDescent() 
    : NodeLayer("TestingLayer"), m_Cam1(glm::vec3(0.0f, 1.0f, 15.5f)), m_Cam2(glm::vec3(0.0f, 1.0f, 15.5f)) {}

void MyTFMDescent::Join()
{
    // Framebuffer instancia y texture specs
    FBTextureProps fbspec{ Engine::p().GetWindow().GetWidth(), Engine::p().GetWindow().GetHeight() };
    m_FrameBuffer = FrameBuffer::Create(fbspec);

    // Create scene ECS   
    m_Scene = std::make_shared<Scene>();

    // ENTITIES
    // CameraMans
    /*Ent_CameraMan1 = m_Scene->CreateEntity("Camera 1");
    Ent_CameraMan1.AddComponent<CameraComponent>(m_Cam1, glm::vec3(0.0f, 1.0f, 15.5f), W_, H_);
    m_CamMan1.TakeCamera(Ent_CameraMan1.GetComponent<CameraComponent>().Camera);*/
    m_CamMan1.TakeCamera(m_Cam1);
    m_CamMan1.SetViewport({W_, H_});

    Ent_CameraMan2 = m_Scene->CreateEntity("Camera 2");
    Ent_CameraMan2.AddComponent<CameraComponent>(m_Cam2, glm::vec3(0.0f, 1.0f, 15.5f), W_, H_);
    Ent_CameraMan2.GetComponent<CameraComponent>().Primary = false;
    m_CamMan2.TakeCamera(Ent_CameraMan2.GetComponent<CameraComponent>().Camera);
    // Light
    Ent_Light = m_Scene->CreateEntity("Directional Light");
    Ent_Light.AddComponent<LightComponent>();
    Ent_Light.AddComponent<MaterialComponent>();
    Ent_Light.GetComponent<MaterialComponent>().SetDefault();
    Ent_Light.GetComponent<TransformComponent>().ID = 3;
    Ent_Light.GetComponent<TransformComponent>().T = Ent_Light.GetComponent<LightComponent>().Position;
    Ent_Light.GetComponent<TransformComponent>().R = Ent_Light.GetComponent<LightComponent>().Direction;
    Ent_Light.GetComponent<TransformComponent>().S = glm::vec3(1.5f, 1.0f, 1.0f);    
    
    for (size_t i = 0; i < 10; ++i)
    {
        const std::string idx = "Point Light " + std::to_string(i + 1);

        Ent_PL[i] = m_Scene->CreateEntity(idx);
        Ent_PL[i].AddComponent<PointLightComponent>();
        Ent_PL[i].GetComponent<TransformComponent>().S = glm::vec3{ 0.3f, 0.3f, 0.3f };
     
        Ent_PL[i].AddComponent<MaterialComponent>();
        Ent_PL[i].GetComponent<MaterialComponent>().SetDefault();
    }   

    for (size_t i = 0; i < 2; ++i)
    {
        const std::string idx = "Spot Light " + std::to_string(i + 1);

        Ent_SL[i] = m_Scene->CreateEntity(idx);
        Ent_SL[i].AddComponent<SpotLightComponent>();
        Ent_SL[i].GetComponent<TransformComponent>().S = glm::vec3{ 0.3f, 0.3f, 0.3f };
        Ent_SL[i].AddComponent<MaterialComponent>();
        Ent_SL[i].GetComponent<MaterialComponent>().SetDefault();
    } 


    m_HierarchyPanel.SetContext(m_Scene);
    SerializerScene serializer(m_Scene);
    serializer.Serialize("../assets/scenes/MyTFMScene.mh");

    // INFO
    m_Vendor   = RenderDrawCall::GetVendor();
    m_Renderer = RenderDrawCall::GetRedenrer();
    m_Version  = RenderDrawCall::GetVersion();
}

void MyTFMDescent::Free() { }

void MyTFMDescent::Update(DeltaTime dt) 
{ 
    m_IsEditScene = Ent_CameraMan1.GetComponent<CameraComponent>().Primary;

    if (m_IsEditScene)
    {
        m_CamMan1.Update(dt);
        m_FrameBuffer->Bind();
    }
    else m_CamMan2.Update(dt);
    {
        RenderDrawCall::ClearColor({ m_BackGroundColor, 1.0f });
        RenderDrawCall::clear();

        m_Scene->Update(dt);
    }
    if (m_IsEditScene)
    {
        m_FrameBuffer->Unbind();    }
    
}

void MyTFMDescent::ImGuiRender()
{
    if (m_IsEditScene)
    {
        static bool docksOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // Estamos usando la bandera ImGuiWindowFlags_NoDocking para hacer que la ventana principal no se pueda acoplar,
        // porque sería confuso tener dos objetivos de acoplamiento entre sí.
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
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

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
      
        ImGui::Begin("Rendering"); // begin 1
        ImGui::NewLine();
       // ImGui::Text(m_Vendor.c_str()  );
        ImGui::Text(m_Renderer.c_str());
        ImGui::Text(m_Version.c_str());
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        ImGui::Text("Active camera");
        // checkbox
        if (ImGui::Checkbox("Editor Camera", &m_PrimaryCam))
        {
            Ent_CameraMan2.GetComponent<CameraComponent>().Primary = !m_PrimaryCam;
            Ent_CameraMan1.GetComponent<CameraComponent>().Primary = m_PrimaryCam;
        }
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        ImGui::Text("Background");
        ImGui::ColorEdit3("Color", glm::value_ptr(m_BackGroundColor));
        

        /* SCENE FRAME */
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

        ImGui::Begin("Scene Frame");
   
        /* FLAG */ // Si cambia el ViewPort del frameImGui donde esta la textura de la escena
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        {
            /* FLAG */ // Si hay foco del mouse sobre el frame del window // no bloquees los eventos desde Event System
           // Ent_CameraMan1.GetComponent<CameraManComponent>().IsHovered = ImGui::IsWindowHovered();
            m_CamMan1._IsWindowHovered = ImGui::IsWindowHovered();
            m_CamMan1._IsWindowFocused = ImGui::IsWindowFocused();

            const float X = Ent_CameraMan1.GetComponent<CameraComponent>().ViewportX;
            const float Y = Ent_CameraMan1.GetComponent<CameraComponent>().ViewportY;

            if ((X != viewportPanelSize.x) || (Y != viewportPanelSize.y))
            {
                Ent_CameraMan1.GetComponent<CameraComponent>().ViewportX = viewportPanelSize.x;
                Ent_CameraMan1.GetComponent<CameraComponent>().ViewportY = viewportPanelSize.y;
            }
        }

        uint32_t textureID = m_FrameBuffer->GetFBOTexture();
        ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        // Gizmo
        Entity EntSelected = m_HierarchyPanel.GetCollectedEntity();

        if (EntSelected && m_GizmoType != -1 && Ent_CameraMan1.GetComponent<CameraComponent>().Primary)
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            float wWidth = (float)ImGui::GetWindowWidth();
            float wHeight = (float)ImGui::GetWindowHeight();

            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, wWidth, wHeight);

            const auto& ECam = Ent_CameraMan1.GetComponent<CameraComponent>();

            // CAMERA
            glm::mat4& Projection = glm::perspective(
                glm::radians
                (
                    ECam.Camera.GetFOV()),
                    ECam.ViewportX / ECam.ViewportY,
                    ECam.Near, ECam.Far
                );

            glm::mat4  ViewMatrix = ECam.Camera.GetViewMatrix();

            // ENTITY TRANSFORM
            auto& TC = EntSelected.GetComponent<TransformComponent>();
            glm::mat4 T = TC.GetTransform();


            ImGuizmo::Manipulate(glm::value_ptr(ViewMatrix), glm::value_ptr(Projection),
                (ImGuizmo::OPERATION)m_GizmoType,
                ImGuizmo::LOCAL,
                glm::value_ptr(T));

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 Tra, Rot, Sca;
                DecomposeTransform(T, Tra, Rot, Sca);
                glm::vec3 DeltaRot = Rot - TC.R;
                TC.T = Tra;
                TC.R += DeltaRot;
                TC.S = Sca;
            }
        }

        ImGui::End(); // end 1
        ImGui::PopStyleVar(); // pop -> PushStyleVar(ImGuiStyleVar_WindowPadding)
        ImGui::End(); // end 2    
        ImGui::End(); // end 2 
    }
    else
    {
        Ent_CameraMan2.GetComponent<CameraComponent>().ViewportX = W_;
        Ent_CameraMan2.GetComponent<CameraComponent>().ViewportY = H_;
    }   
}

void MyTFMDescent::OnEvent(Event& event) 
{
	
    if (Ent_CameraMan1)
    {
        if (Ent_CameraMan1.GetComponent<CameraComponent>().Primary)
        {

            if (m_Editor_Cam_FirtsUse)
            {
                m_Editor_Cam_FirtsUse = false;
                m_CamMan1._Mouse = false;
            }

            if (m_CamMan1._IsWindowHovered)
            {
                if (event.GetEventType() == IsType::MH_MOUSE_BUTTON_PRESSED)
                {
                    if (dynamic_cast<OnMouseButtonPressed&>(event).GetMouseButton() == 1)
                    {
                        m_CamMan1._Mouse = true;
                        m_CamMan1.SetCaptureMode(true);
                    }
                }

                if (event.GetEventType() == IsType::MH_MOUSE_BUTTON_RELEASED)
                {
                    m_CamMan1._Mouse = false;
                    m_CamMan1.SetCaptureMode(false);
                }
            }
            
          
            m_CamMan1.OnEvent(event);
        }
    }
    if (Ent_CameraMan2)
    {
        if (Ent_CameraMan2.GetComponent<CameraComponent>().Primary)
        {
            m_CamMan2.OnEvent(event);
        }
    }

	if (event.GetEventType() == IsType::MH_KEY_PRESSED)
	{


        if (m_CamMan1._IsWindowFocused || m_CamMan1._IsWindowHovered)
        {
            OnKeyPressed& e = dynamic_cast<OnKeyPressed&>(event);

            switch (e.GetKeyCode())
            {
                case Key::Q:
                    m_GizmoType = -1; break;
                case Key::D1:
                    m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;  break;
                case Key::D2:
                    m_GizmoType = ImGuizmo::OPERATION::ROTATE;     break;
                case Key::D3:
                    m_GizmoType = ImGuizmo::OPERATION::SCALE;      break;

                case Key::M:
                    // hack -> recupera el puntero del raton en el editor
                    Engine::p().GetWindow().SetCaptureMode(false);
                    break;

                case Key::C:
                {
                    m_PrimaryCam = false;
                    Ent_CameraMan2.GetComponent<CameraComponent>().Primary = true;
                    Ent_CameraMan1.GetComponent<CameraComponent>().Primary = false;
                    break;
                }
                case Key::V:
                {
                    m_PrimaryCam = true;
                    Ent_CameraMan2.GetComponent<CameraComponent>().Primary = false;
                    Ent_CameraMan1.GetComponent<CameraComponent>().Primary = true;
                    break;
                }
            }
        }		       
	}
}
