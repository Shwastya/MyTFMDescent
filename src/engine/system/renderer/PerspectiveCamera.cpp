#include "engine/system/renderer/PerspectiveCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

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

    void PerspectiveCamera::setNewPosition(const glm::vec3& stride)
    {
        m_Position *= stride;
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
        const float velocity = k_Speed * dt.Seconds();

        // SEGURAMENTE NO LO VOLVERE A USAR (BORRAR?)
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
        const float xoff = xoffset * k_Sensitivity;
        const float yoff = yoffset * k_Sensitivity;

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
        if (m_Fov >= 1.0f && m_Fov <= 45.0f) m_Fov -= yoffset;
        if (m_Fov <= 1.0f) m_Fov = 1.0f;
        if (m_Fov >= 45.0f) m_Fov = 45.0f;
    }

    void PerspectiveCamera::Forward(DeltaTime dt)
    {
        const float velocity = k_Speed * dt.Seconds();
        m_Position += m_Front * velocity;
    }

    void PerspectiveCamera::Backward(DeltaTime dt)
    {
        const float velocity = k_Speed * dt.Seconds();
        m_Position -= m_Front * velocity;
    }

    void PerspectiveCamera::Left(DeltaTime dt)
    {
        const float velocity = k_Speed * dt.Seconds();
         m_Position -= m_Right * velocity;
    
    }

    void PerspectiveCamera::Right(DeltaTime dt)
    {
        const float velocity = k_Speed * dt.Seconds();
        m_Position += m_Right * velocity;
    }
}



