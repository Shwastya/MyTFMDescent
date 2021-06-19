#pragma once
#include "../src/engine/mhpch.cpp"

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

		/* App types */
		MH_APP_TICK,
		MH_APP_UPDATE,
		MH_APP_RENDER,

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

	enum IsInCategory
	{
		NONE = 0,
		MH_CATG_APP			  = (1 << 0),
		MH_CATG_INPUT		  = (1 << 1),
		MH_CATG_KEYBOARD	  = (1 << 2),
		MH_CATG_MOUSE		  = (1 << 3),
		MH__CATG_MOUSE_BUTTON = (1 << 4),
	};

	class Event
	{
	public:
		bool Handled = false;

		virtual ~Event() = default;

		virtual IsType GetEventType()	const = 0;	
		virtual int GetCategoryFlags()		const = 0;

		inline bool IsInCategory(IsInCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};	


}

