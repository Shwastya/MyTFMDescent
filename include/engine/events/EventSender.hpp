#pragma once

#include "Event.hpp"

namespace MHelmet
{
    struct EventSender
	{

		EventSender(Event& event) 
			: m_Event(event) {}

		template<typename T>
		bool Send(std::function<bool(T&)> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};	
}

