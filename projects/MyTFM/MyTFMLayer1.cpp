#include "MyTFMLayer1.hpp"
#include <ImGuizmo.h>
#include "engine/system/scene/SerializerScene.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"
#include "engine/system/scene/Components.hpp"

#define W_ static_cast<float>(Engine::p().GetWindow().GetWidth())
#define H_ static_cast<float>(Engine::p().GetWindow().GetHeight())

MyTFMDescent::MyTFMDescent() : NodeLayer("TestingLayer") {}

void MyTFMDescent::Join()
{    

    

    FBProps fbprops;
    fbprops.List = { FBTextureFormat::RGBA8, FBTextureFormat::REDINTEGER, FBTextureFormat::DEPTHCOMPONENT24};

    fbprops.W = 1176;
    fbprops.H = 1036;
    
    FBProps fbprops2;
    fbprops2.List = { FBTextureFormat::RGBA8};

    fbprops2.W = 1176;
    fbprops2.H = 1036;

    FBProps fbprops3;
    fbprops3.List = { FBTextureFormat::RGBA8 };

    fbprops3.W = Engine::p().GetWindow().GetWidth();
    fbprops3.H = Engine::p().GetWindow().GetHeight();


    m_FramebufferFirstScene   = FrameBuffer::Create(fbprops);
    m_FramebufferImGuiFrame   = FrameBuffer::Create(fbprops2);
    m_FramebufferPlayerCamera = FrameBuffer::Create(fbprops3);

    // Create scene ECS   
    m_Scene = std::make_shared<Scene>();

   

    m_Cam1 = glm::vec3(0.0f, 1.0f, 15.5f);
    m_CamMan1.TakeCamera(m_Cam1);
    m_CamMan1.SetViewport({ 1176.0f, 1036.0f });

    m_Cam2 = glm::vec3(0.0f, 1.0f, 15.5f);
    m_CamMan2.TakeCamera(m_Cam2);
    m_CamMan2.SetViewport({ W_, H_ });
    
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
   // SerializerScene serializer(m_Scene);
   // serializer.Serialize("../assets/scenes/MyTFMScene.mh");

    // INFO
    m_Vendor   = RenderDrawCall::GetVendor();
    m_Renderer = RenderDrawCall::GetRedenrer();
    m_Version  = RenderDrawCall::GetVersion();
}

void MyTFMDescent::Free() { }

void MyTFMDescent::Update(TimeStep dt)
{     
    if (m_IsEditScene)
    {
        
        m_CamMan1.Update(dt);     
        RenderDrawCall::ClearColor({ m_BackGroundColor, 1.0f });
        
        
        // FIRST RENDER PASS
        {
           
            m_FramebufferFirstScene->Bind();
            {
                RenderDrawCall::EnableDepthTest();
                RenderDrawCall::clear();
                m_Scene->UpdateFirstPersonCamera(dt, m_CamMan1);
            }           
            m_FramebufferFirstScene->Unbind();
        }
        // SECOND PASS
        {
            m_FramebufferImGuiFrame->Bind();
            {
                RenderDrawCall::DisableDepthTest();
                RenderDrawCall::ClearColorBufferOnly();
                m_Scene->UpdateScreenTexture(m_FramebufferFirstScene);
            }
            m_FramebufferImGuiFrame->Unbind();
        }
        // FRAME GAME PLAY
        {
            RenderDrawCall::SetWiewPort(0, 0, Engine::p().GetWindow().GetWidth(), Engine::p().GetWindow().GetHeight());            

            m_FramebufferPlayerCamera->Bind();
            {    
                RenderDrawCall::EnableDepthTest();
                RenderDrawCall::clear();
                m_Scene->UpdateFirstPersonCamera(dt, m_CamMan2);
            }
            m_FramebufferPlayerCamera->Unbind();
        }
       
    }
    else
    {
     m_CamMan2.SetViewport({ (float)Engine::p().GetWindow().GetWidth(), (float)Engine::p().GetWindow().GetHeight() });
     m_CamMan2.Update(dt);
    // RenderDrawCall::SetWiewPort(0, 0, Engine::p().GetWindow().GetWidth(), Engine::p().GetWindow().GetHeight());
     
     RenderDrawCall::clear();
     m_Scene->UpdateFirstPersonCamera(dt, m_CamMan2);
   
    }
}

void MyTFMDescent::ImGuiRender()
{
    if (m_IsEditScene)
    {
        m_DockSpace.Begin(); // INIT DOCKS SPACE
        {
            m_MenuBar.ImGuiRender();
            m_HierarchyPanel.ImGuiRender();
            m_BrowserPanel.ImGuiRender();



            /* My ImGui SETTINGS */
            ImGui::Begin("Rendering");

            ImGui::Text("Active camera");
            // checkbox
            if (ImGui::Checkbox("Editor Camera", &m_IsEditScene))
            {
                m_IsEditScene = (m_IsEditScene) ? true : false;
            }

            if (ImGui::Checkbox("Activate post-process", &m_EnablePostProcess))
            {
                m_EnablePostProcess = (m_EnablePostProcess) ? true : false;
            }
            ImGui::Separator();
            ImGui::Text("Background");
            ImGui::ColorEdit3("Color", glm::value_ptr(m_BackGroundColor));

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin("Player Camera");

            {
                ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
                {

                    if (m_CamMan2.GetViewPort() != *((glm::vec2*)&viewportPanelSize))
                    {
                        m_CamMan2.SetViewport({ viewportPanelSize.x, viewportPanelSize.y });
                    }
                }
                uint32_t texturePlayCamID = m_FramebufferPlayerCamera->GetFBOTexture(0);
                ImGui::Image((void*)texturePlayCamID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
            }

            ImGui::End();
            ImGui::PopStyleVar();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

            ImGui::Begin("Scene Frame");
            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
            {
                m_CamMan1._IsWindowHovered = ImGui::IsWindowHovered();
                m_CamMan1._IsWindowFocused = ImGui::IsWindowFocused();

                if (m_viewPortSize != *((glm::vec2*)&viewportPanelSize))
                {
                    m_CamMan1.SetViewport({ viewportPanelSize.x, viewportPanelSize.y });

                    m_FramebufferFirstScene->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
                    //m_FramebufferImGuiFrame->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
                    m_viewPortSize = { viewportPanelSize.x, viewportPanelSize.y };

                }

            }
            //  uint32_t textureID = m_FramebufferImGuiFrame->GetFBOTexture(0);
            if (m_EnablePostProcess)
                ImGui::Image((void*)m_FramebufferImGuiFrame->GetFBOTexture(0), ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
            else
                ImGui::Image((void*)m_FramebufferFirstScene->GetFBOTexture(0), ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

            ImGui::PopStyleVar(); // pop -> PushStyleVar(ImGuiStyleVar_WindowPadding)





            // Gizmo
            Entity EntSelected = m_HierarchyPanel.GetCollectedEntity();

            if (EntSelected && m_GizmoType != -1 && m_IsEditScene)
            {
                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist();

                float wWidth = (float)ImGui::GetWindowWidth();
                float wHeight = (float)ImGui::GetWindowHeight();

                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, wWidth, wHeight);

                // const auto& ECam = Ent_CameraMan1.GetComponent<CameraComponent>();

                 // CAMERA
                glm::mat4& Projection = glm::perspective
                (
                    glm::radians
                    (
                        m_CamMan1.Get().GetFOV()),
                    m_CamMan1.GetViewPort().x / m_CamMan1.GetViewPort().y,
                    m_CamMan1.GetNear(), m_CamMan1.GetFar()

                );

                glm::mat4  ViewMatrix = m_CamMan1.Get().GetViewMatrix();

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
            ImGui::End(); // end 2  
        }        
        m_DockSpace.End(); // END DOCK SPACE
    }
}

void MyTFMDescent::OnEvent(Event& event) 
{
	
    //if (Ent_CameraMan1)
    {
        if (m_IsEditScene)
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
        else
        {
            m_CamMan2.SetCaptureMode(true);
            m_CamMan2.OnEvent(event);
        }
    }

	if (event.GetEventType() == IsType::MH_KEY_PRESSED)
	{


        if (m_CamMan1._IsWindowFocused || m_CamMan1._IsWindowHovered)
        {
            //OnKeyPressed& e = dynamic_cast<OnKeyPressed&>(event);

            switch (dynamic_cast<OnKeyPressed&>(event).GetKeyCode())
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
                
            }
        }

        if (dynamic_cast<OnKeyPressed&>(event).GetKeyCode() == MH_KEY_C) m_IsEditScene = false;
        if (dynamic_cast<OnKeyPressed&>(event).GetKeyCode() == MH_KEY_V)
        {
            Engine::p().GetWindow().SetCaptureMode(false);
            m_IsEditScene = true;
        }
            
	}
}
