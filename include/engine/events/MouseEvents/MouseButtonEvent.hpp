#pragma once

#include <sstream>
#include "../Event.hpp"

namespace MHelmet {

    struct MouseButtonEvent : public Event
    {
        inline int GetMouseButton() const { return m_Button; }

        virtual inline int GetCategoryFlags() const override 
        { 
            return E_CATG_MOUSE | E_CATG_INPUT;
        }

    protected:

        MouseButtonEvent(int button) : m_Button(button) {}
        int m_Button;
    };
}