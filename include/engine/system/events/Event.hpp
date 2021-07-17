#pragma once
#include <MHpch.h>

namespace MHelmet 
{
	enum class IsType
	{
		NONE = 0,		
		/* Window types */
		MH_WINDOW_CLOSE,
		MH_WINDOW_RESIZE,
		MH_WINDOW_FOCUS,
		MH_WINDOW_LOST_FOCUS,
		MH_WINDOW_MOVED,

		/* Key types */
		MH_KEY_PRESSED,
		MH_KEY_RELEASED,
		MH_KEY_TYPED,

		/* Mouse types */
		MH_MOUSE_BUTTON_PRESSED,
		MH_MOUSE_BUTTON_RELEASED,
		MH_MOUSE_MOVED,
		MH_MOUSE_SCROLLED,
	};	

	class Event
	{
	public:
		bool Handled = false;
		virtual ~Event() = default;
		virtual IsType GetEventType()	const = 0;	
	};	


}

