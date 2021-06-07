#pragma once

#include <sstream>

#include <MHKeyCodes.h>
#include "../Event.hpp"


namespace MHelmet 
{    

	class KeyEvent : public Event
	{
	public:
		inline KeyCode GetKeyCode() const 
        { 
            return m_KeyCode; 
        }
		inline virtual int GetCategoryFlags() const override 
        { 
            return E_CATG_KEYBOARD | E_CATG_INPUT;
        }

	protected:
		KeyEvent(KeyCode keycode) : m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};
}

