#include "engine/system/renderer/PerspectiveCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/system/Input.hpp"
#include <engine/system/MHCore.hpp>

namespace MHelmet
{
    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
        : m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_Fov(k_FOV)
    {
        UpdateCameraVectors();
    }

    PerspectiveCamera::PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : m_Position(glm::vec3(posX, posY, posZ)), m_WorldUp(glm::vec3(upX, upY, upZ)), m_Yaw(yaw), m_Pitch(pitch), m_Fov(k_FOV)
    {
        UpdateCameraVectors();
    }


    glm::mat4 PerspectiveCamera::GetViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    float PerspectiveCamera::GetFOV() const
    {
        return m_Fov;
    }

    glm::vec3 PerspectiveCamera::GetPosition() const
    {
        return m_Position;
    }

    void PerspectiveCamera::UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }

    void PerspectiveCamera::HandleKeyboard(Movement direction, DeltaTime dt)
    {
        const float velocity = m_Speed * dt.Seconds();

        // Ahora mismo no se esta usando
        switch (direction)
        {
            case Movement::Forward:  m_Position += m_Front * velocity; break;
            case Movement::Backward: m_Position -= m_Front * velocity; break;
            case Movement::Left:     m_Position -= m_Right * velocity; break;
            case Movement::Right:    m_Position += m_Right * velocity; break;
        }
    }

    void PerspectiveCamera::HandleMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        const float xoff = xoffset * m_Sensitivity;
        const float yoff = yoffset * m_Sensitivity;

        m_Yaw += xoff;
        m_Pitch += yoff;

        if (constrainPitch)
        {
            if (m_Pitch > 89.0f) m_Pitch = 89.0f;
            if (m_Pitch < -89.0f) m_Pitch = -89.0f;
        }

        UpdateCameraVectors();
    }

    void PerspectiveCamera::HandleMouseScroll(float yoffset)
    {
        if (m_Fov >= 0.1f && m_Fov <= 140.0f) m_Fov -= yoffset;
        if (m_Fov <= 0.1f) m_Fov = 0.1f;
        if (m_Fov >= 140.0f) m_Fov = 140.0f;
    }

    void PerspectiveCamera::Forward(float dt)
    {
        const float velocity = m_Speed * dt;
        m_Position += m_Front * velocity;
    }

    void PerspectiveCamera::Backward(float dt)
    {
        const float velocity = m_Speed * dt;
        m_Position -= m_Front * velocity;
    }

    void PerspectiveCamera::Left(float dt)
    {
        const float velocity = m_Speed * dt;
         m_Position -= m_Right * velocity;
    
    }

    void PerspectiveCamera::Right(float dt)
    {
        const float velocity = m_Speed * dt;
        m_Position += m_Right * velocity;
    }



    //////////////////////////////////////////////////////
    ////                CAMERA MANAGER                 ///
    //////////////////////////////////////////////////////

    CameraMan::CameraMan(glm::vec3 position)
        : m_Cam(position), m_InitalPosition(position)
    {}

    void CameraMan::Update(DeltaTime dt)
    {
        if (Input::IsKeyPressed(MH_KEY_S)) m_Cam.Backward(dt.Seconds());
     
        if (Input::IsKeyPressed(MH_KEY_W)) m_Cam.Forward(dt.Seconds());
        
        if (Input::IsKeyPressed(MH_KEY_A)) m_Cam.Left(dt.Seconds());
        
        if (Input::IsKeyPressed(MH_KEY_D)) m_Cam.Right(dt.Seconds());        
    }

    void CameraMan::OnEvent(Event& e)
    {
        if (e.GetEventType() == IsType::MH_MOUSE_MOVED)
        {
            MouseMoved(dynamic_cast<OnMouseMoved&>(e));
        }

        if (e.GetEventType() == IsType::MH_MOUSE_SCROLLED && _Scroll)
        {
            m_Cam.HandleMouseScroll(dynamic_cast<OnMouseScrolled&>(e).GetYOffset());            
        }
    }

    bool CameraMan::MouseMoved(OnMouseMoved& e)
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

        if (_Mouse) m_Cam.HandleMouseMovement(Xoffset, Yoffset);
        return false;
    }
}



