#pragma once
#include <glm/glm.hpp>
#include "../src/engine/mhpch.cpp"

#include "engine/system/utils/utils.hpp"
#include "engine/system/events/AppEvents/OnAppEvents.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"

namespace MHelmet
{    
    const float k_Yaw = -90.0f;
    const float k_Pitch = 0.0f;    
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

        void Forward(float dt);
        void Backward(float dt);
        void Left(float dt);
        void Right(float dt);

        void SetSpeed(float speed) { m_Speed = speed; };
        void SetSensitivity(float sens) { m_Sensitivity = sens; };       

    private:
        void UpdateCameraVectors();

    private:
        glm::vec3 m_Position;  
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;

        float m_Yaw;
        float m_Pitch;
        float m_Fov;

    private:
        float m_Speed = 3.5f;
        float m_Sensitivity = 0.1f;
    };


    //////////////////////////////////////////////////////
    ////                CAMERA MANAGER                 ///
    //////////////////////////////////////////////////////

    struct CameraMan
    {
        CameraMan(glm::vec3 position);

        void Update(DeltaTime dt);
        void OnEvent(Event& e);

        bool MouseMoved(OnMouseMoved& e);

        PerspectiveCamera& Get() { return m_Cam; };
        const PerspectiveCamera& Get() const { return m_Cam; };

        void Speed(float speed) { m_Cam.SetSpeed(speed); }
        void Sensitivity(float Sensitivity) { m_Cam.SetSensitivity(Sensitivity); };

        bool _Input  = true;
        bool _Mouse  = true;
        bool _Scroll = true;

    private:
        PerspectiveCamera m_Cam;
        glm::vec3 m_InitalPosition;

    private: // Mouse attributes        
        bool m_FirstMouse = true;
        float m_LastX = 0.0f;
        float m_LastY = 0.0f;        
    };
}




