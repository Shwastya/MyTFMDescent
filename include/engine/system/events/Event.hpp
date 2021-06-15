#pragma once
#include "../src/engine/mhpch.cpp"

namespace MHelmet 
{
	enum class EventType
	{
		NONE = 0,		
		/* Window types */
		E_WINDOW_CLOSE,
		E_WINDOW_RESIZE,		
		E_WINDOW_FOCUS,
		E_WINDOW_LOST_FOCUS,
		E_WINDOW_MOVED,		

		/* App types */
		E_APP_TICK,
		E_APP_UPDATE,
		E_APP_RENDER,		

		/* Key types */
		E_KEY_PRESSED,
		E_KEY_RELEASED,
		E_KEY_TYPED,		

		/* Mouse types */
		E_MOUSE_BUTTON_PRESSED,
		E_MOUSE_BUTTON_RELEASED,
		E_MOUSE_MOVED,
		E_MOUSE_SCROLLED,	
	};	

	enum EventCategory
	{
		NONE = 0,
		E_CATG_APP			= (1 << 0),
		E_CATG_INPUT		= (1 << 1),
		E_CATG_KEYBOARD		= (1 << 2),	
		E_CATG_MOUSE		= (1 << 3),
		E_CATG_MOUSE_BUTTON = (1 << 4),		
	};

	class Event
	{
	public:
		bool Handled = false;

		virtual ~Event() = default;

		virtual EventType GetEventType()	const = 0;	
		virtual int GetCategoryFlags()		const = 0;
		virtual std::string Print()		const = 0;

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		// Solo para propositos de debug
		virtual std::string GetName()  const = 0;
	};	


	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{		
		return os << event.Print();
	}
}

