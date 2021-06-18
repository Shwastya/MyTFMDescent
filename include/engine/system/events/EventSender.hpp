#pragma once

#include "Event.hpp"

namespace MHelmet
{
    struct EventHandler
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

		EventHandler(Event& event)
			: m_Event(event) 
		{

		}

		template<typename T>
		bool CallBack(EventFn<T> func)
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

