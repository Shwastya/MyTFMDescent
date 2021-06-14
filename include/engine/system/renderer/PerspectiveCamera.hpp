#pragma once
#include <glm/glm.hpp>
#include "engine/system/MHCore.hpp"

namespace MHelmet
{
    const float k_Yaw = -90.0f;
    const float k_Pitch = 0.0f;
    const float k_Speed = 1.5f;
    const float k_Sensitivity = 0.1f;
    const float k_FOV = 45.0f;

    class PerspectiveCamera 
    {
    public:
        enum class Movement 
        {
            Forward = 0,
            Backward = 1,
            Left = 2,
            Right = 3,
        };

        PerspectiveCamera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = k_Yaw, float pitch = k_Pitch);
        PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 GetViewMatrix() const;
        float GetFOV() const;
        glm::vec3 GetPosition() const;

        void HandleKeyboard(Movement direction, DeltaTime dt);
        void HandleMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void HandleMouseScroll(float yoffset);


        void Forward(DeltaTime dt);
        void Backward(DeltaTime dt);
        void Left(DeltaTime dt);
        void Right(DeltaTime dt);

    private:
        void UpdateCameraVectors();
    private:
        glm::vec3 m_Position, m_Front, m_Up, m_Right, m_WorldUp;
        float m_Yaw, m_Pitch;
        float m_Fov;
    };
}




