#pragma once
#include <MHpch.h>
#include "engine/system/MHCore.hpp"

namespace MHelmet 
{	
	struct Size 
	{ 
		uint32_t Width = 0;
		uint32_t Height = 0; 
	};

	struct Position { float X = 0.0f; float Y = 0.0f; };

	// Window Specification 
	struct WindowSpec 
	{
		//WindowSpec() = default;
		WindowSpec(const std::string& title = "Mhelmet window", uint32_t W = 1920, uint32_t H = 1080)
			: Title(title), 
			  Size{ W, H },
			  FullScreen(false),
			  VSync(true) {}

		std::string Title;
		Size  Size;
		bool FullScreen;
		bool VSync;
	};	

	struct Window
	{	
		virtual ~Window() {}

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0; // updating

		virtual void Maximize() = 0;

		virtual uint32_t  GetWidth()  const = 0;
		virtual uint32_t  GetHeight() const = 0;

		virtual Size      GetSize()   const = 0;
		virtual Position  GetPos()    const = 0;

		virtual void* GetOriginalWindow()	 const = 0;
		
		virtual void SetCallBack(const std::function<void(Event&)>& cb) = 0;

		virtual void SetVSync(bool toggle) = 0;
		virtual bool IsVSync() const = 0;	
		virtual void SetCaptureMode(bool toggle) const = 0;

		// NOTA
		// Aqui para que fuera independientemente de la plataforma
		// haria falta un tipo de declaracion switch (podria ser a nivel de pre-proceso)
		static Unique<Window> Create(const WindowSpec& spec = WindowSpec());
	};
}