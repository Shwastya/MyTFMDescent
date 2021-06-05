#pragma once
#include "engine/MHCore.hpp"
#include <functional>


namespace MHelmet {
	
	/**************************** NOTA: *****************************/
	// glfwCreateWindow -> he visto casos que castean a (int)
	// y yo estoy usando uint32_t. De momento no he tenido problema
	// pero lo dejo como NOTA por si en el futuro tuviera problemas
	// poder disponer de todas las pistas posibles
	/****************************************************************/
	struct UI_Vec { uint32_t Width = 0, Height = 0;    };
	struct FL_Vec { float Width = 0.0f, Height = 0.0f; };

	struct WindowSpec /* Window Specification */
	{
		const char* Title = MH_TITLE;
		UI_Vec  Size	  = { MH_WIDTH, MH_HEIGHT };
		bool FullScreen	  = MH_FULL_SRC;
		bool VSync		  = MH_VSYNC;
	};	

	struct Window
	{		
		virtual ~Window() {}

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual uint32_t GetWidth()  const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual UI_Vec GetSize()  const = 0;
		virtual FL_Vec GetPos()   const = 0;

		virtual void Maximize() = 0;

		virtual void SetVSync(bool toggle) = 0;
		virtual bool IsVSync() const = 0;


		static Window* Create(const WindowSpec& spec = WindowSpec());
	};
}