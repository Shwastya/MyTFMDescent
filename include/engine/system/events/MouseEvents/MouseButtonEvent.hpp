#pragma once

#include <sstream>
#include "../Event.hpp"

namespace MHelmet {

    struct MouseButtonEvent : public Event
    {
        int GetMouseButton() const 
        { 
            return m_Button; 
        }

    protected:

        MouseButtonEvent(int button) 
            : m_Button(button) {}

        int m_Button;
    };
}