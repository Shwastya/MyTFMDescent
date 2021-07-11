#include "engine/system/cameraManager/CameraEditor.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/system/Input.hpp"
#include <engine/system/MHCore.hpp>
#include "../src/engine/mhpch.cpp"
#include "engine/system/utils/utils.hpp"
#include "engine/system/events/AppEvents/OnAppEvents.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"
#include "engine/engine.hpp"

namespace MHelmet
{
    void CameraEditor::Update(DeltaTime dt)
    {
        if (_IsWindowHovered)
        {
            //if (Input::IsKeyPressed(Key::LeftAlt))
            //{
            //    const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
            //   // glm::vec2 delta = (mouse - m_)
            //}

            if (Input::IsKeyPressed(MH_KEY_S)) HandleKeyboard(Movement::Backward, dt);

            if (Input::IsKeyPressed(MH_KEY_W)) HandleKeyboard(Movement::Forward, dt);

            if (Input::IsKeyPressed(MH_KEY_A)) HandleKeyboard(Movement::Left, dt);

            if (Input::IsKeyPressed(MH_KEY_D)) HandleKeyboard(Movement::Right, dt);
        }
    }

    void CameraEditor::OnEvent(Event& e)
    {
        if (_IsWindowHovered)
        {
            if (e.GetEventType() == IsType::MH_MOUSE_MOVED)
                MouseMoved(dynamic_cast<OnMouseMoved&>(e));

            if (e.GetEventType() == IsType::MH_MOUSE_SCROLLED)
                HandleMouseScroll(dynamic_cast<OnMouseScrolled&>(e).GetYOffset());
        }

    }

    void CameraEditor::HandleKeyboard(Movement direction, DeltaTime dt)
    {

        const float velocity = m_Speed * dt.Seconds();

        switch (direction)
        {
        case Movement::Forward:  CAM.Position() += CAM.Front() * velocity; break;

        case Movement::Backward: CAM.Position() -= CAM.Front() * velocity; break;

        case Movement::Left:     CAM.Position() -= CAM.Right() * velocity; break;

        case Movement::Right:    CAM.Position() += CAM.Right() * velocity; break;
        }

        if (!m_FlightMode) CAM.Position().y = 0.0f;
    }

    void CameraEditor::HandleMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        const float xoff = xoffset * m_Sensitivity;
        const float yoff = yoffset * m_Sensitivity;

        CAM.Yaw() += xoff;
        CAM.Pitch() += yoff;

        if (constrainPitch)
        {
            if (CAM.Pitch() > 89.0f)  CAM.Pitch() = 89.0f;
            if (CAM.Pitch() < -89.0f) CAM.Pitch() = -89.0f;
        }
        CAM.UpdateCameraVectors();
    }

    void CameraEditor::HandleMouseScroll(float yoffset)
    {
        if (CAM.Fov() >= 0.1f && CAM.Fov() <= 140.0f) CAM.Fov() -= yoffset;
        if (CAM.Fov() <= 0.1f) CAM.Fov() = 0.1f;
        if (CAM.Fov() >= 140.0f) CAM.Fov() = 140.0f;
    }

    bool CameraEditor::MouseMoved(OnMouseMoved& e)
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

        if (_Mouse) HandleMouseMovement(Xoffset, Yoffset);

        return false;
    }
    void CameraEditor::SetCaptureMode(const bool mode)
    {
        Engine::p().GetWindow().SetCaptureMode(mode);
    }
}