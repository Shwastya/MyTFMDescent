#pragma once

#include <sstream>

#include <MHKeyCodes.h>
#include "../Event.hpp"


namespace MHelmet 
{    

	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(KeyCode keycode) : m_KeyCode(keycode) {}
		KeyCode m_KeyCode;
	};
}

