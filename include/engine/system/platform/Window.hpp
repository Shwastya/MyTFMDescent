#pragma once
#include "engine/system/MHCore.hpp"
#include <functional>

//#define CALLBACK std::function<void(Event&)>

namespace MHelmet {
	
	/**************************** NOTA: *****************************/
	// glfwCreateWindow -> he visto casos que castean a (int)
	// y yo estoy usando uint32_t. De momento no he tenido problema
	// pero lo dejo como NOTA por si en el futuro tuviera problemas
	// poder disponer de todas las pistas posibles
	/****************************************************************/
	struct Size_Vec { uint32_t Width = 0, Height = 0;    };
	struct Pos_Vec { float X = 0.0f, Y = 0.0f; };

	struct WindowSpec /* Window Specification */
	{
		std::string Title = MH_TITLE;
		Size_Vec  Size	  = { MH_WIDTH, MH_HEIGHT };
		bool FullScreen	  = MH_FULL_SRC;
		bool VSync		  = MH_VSYNC;
	};	

	struct Window
	{	
		virtual ~Window() {}

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0; // updating

		virtual void Maximize() = 0;

		virtual uint32_t GetWidth()  const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual Size_Vec GetSize()   const = 0;
		virtual Pos_Vec  GetPos()    const = 0;

		virtual void* GetWindow()	 const = 0;

		
		virtual void SetCallBack(const CALLBACK& cb) = 0;

		virtual void SetVSync(bool toggle) = 0;
		virtual bool IsVSync() const = 0;		

		// NOTA
		// Aqui para que fuera independientemente de la plataforma
		// haria falta un tipo de declaracion switch (podria ser a nivel de pre-proceso)
		static Window* Create(const WindowSpec& spec = WindowSpec());
	};
}