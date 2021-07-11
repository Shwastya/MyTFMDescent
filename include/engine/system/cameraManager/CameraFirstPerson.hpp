#pragma once
#include "engine/system/renderer/PerspectiveCamera.hpp"


namespace MHelmet
{   
    struct CameraFirstPerson
    {
        enum class Movement
        {
            Forward  = 0,
            Backward = 1,
            Left     = 2,
            Right    = 3,
        };       

        CameraFirstPerson() = default;

        void TakeCamera(PerspectiveCamera& camera) { CAM = camera; };

        void Update(DeltaTime dt);
        void OnEvent(Event& e);

        bool MouseMoved(OnMouseMoved& e);

        PerspectiveCamera& Get() { return CAM; };
        const PerspectiveCamera& Get() const { return CAM; };

        void SetSpeed(const float& speed) { m_Speed = speed; }
        void SetSensitivity(const float& Sensitivity) { m_Sensitivity = Sensitivity; };
        void SetFlightMode(const bool mode) { m_FlightMode = mode; }
        void SetCaptureMode(const bool mode);
        void SetViewport(const glm::vec2 viewport) { m_Viewport = viewport; }


        float GetNear() const { return m_Near; }
        float GetFar()  const { return m_Far; }

        float& FOV() { return CAM.Fov(); }     
        glm::vec2 GetViewPort() const { return m_Viewport; }


        bool _Mouse  = true;
       // bool _Scroll = true;   
        bool _IsWindowHovered = true;
        bool _IsWindowFocused = true;        

    private:
        void HandleKeyboard(Movement dir, DeltaTime dt);
        void HandleMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void HandleMouseScroll(float yoffset);

        void MousePan(const glm::vec2& delta);
        void MouseRotate(const glm::vec2& delta);
        void MouseZoom(float delta);

        glm::vec3 CalculatePosition() const;

       // std::pair<float, float> PanSpeed() const;
        float RotationSpeed() const;
        float ZoomSpeed() const;

    private:
        PerspectiveCamera CAM;

        float m_Near = 0.1f;
        float m_Far = 100.0f;

        glm::vec2 m_Viewport = glm::vec2{ 0.0f, 0.0f };
        glm::vec3 m_InitalPosition = glm::vec3{ 0.0f, 0.0f, 0.0f };

    private:
        float m_Speed = 7.5f;
        float m_Sensitivity = 0.1f;



    private:
       
        bool m_FlightMode = true;      

    private:
            
        glm::vec2 m_InitialMousePosition;

        bool  m_FirstMouse = true;
        float m_LastX = 0.0f;
        float m_LastY = 0.0f;
    };
}