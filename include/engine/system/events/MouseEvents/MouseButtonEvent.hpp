#pragma once

#include <sstream>
#include "../Event.hpp"

namespace MHelmet {

    struct MouseButtonEvent : public Event
    {
        int GetMouseButton() const { return m_Button; }

        virtual int GetCategoryFlags() const override 
        { 
            return MH_CATG_MOUSE | MH_CATG_INPUT;
        }

    protected:

        MouseButtonEvent(int button) : m_Button(button) {}
        int m_Button;
    };
}