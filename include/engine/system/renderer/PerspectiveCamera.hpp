#pragma once
#include <glm/glm.hpp>

namespace MHelmet
{    
    struct TimeStep;
    struct OnMouseMoved;
    class  Event;

    const float k_Yaw = -90.0f;
    const float k_Pitch = 0.0f;    
    const float k_FOV = 45.0f;

    class PerspectiveCamera 
    {
    public:

        PerspectiveCamera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = k_Yaw, float pitch = k_Pitch);
        PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 GetViewMatrix() const;
        float GetFOV() const { return m_Fov; };
        glm::vec3 GetPosition() const { return m_Position; };

        void UpdateCameraVectors();     

        //  input movements
        glm::vec3& Position() { return m_Position; }
        glm::vec3& Front()    { return m_Front;    }
        glm::vec3& Right()    { return m_Right;    }

        //  mouse movement
        float& Yaw()   { return m_Yaw;   }
        float& Pitch() { return m_Pitch; }

        //  mouse scroll
        float& Fov()   { return m_Fov; }

    private:
        glm::vec3 m_Position;  
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;

        float m_Yaw;
        float m_Pitch;
        float m_Fov;

        // las siguientes propiedades deben pertenecer a la camara perspective
        // y no al manager. manejar desde el manager como clase derivada
        float m_Near = 0.1f;
        float m_Far = 100.0f;

        glm::vec2 m_Viewport = glm::vec2{ 0.0f, 0.0f };

 

       
    };   
}




