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
}



