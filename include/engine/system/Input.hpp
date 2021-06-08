#pragma once
// INPUT POLLIN - STATIC  GLOBAL MANAGER
#include <MHkeyCodes.h>

// Tenemos un event system, podemos recibir eventos de tipo key, mouse y app
// Tratandose de un sistema de layers necesitamos empaquetar los cambios de estado
// de alguna manera para poder administrar bien como se propogan estos eventos
// y poder traducir las abstracciones a conceptos mas reales relacionados con la 
// aplicacion.

// En caso de querer tener multiples ventanas, siendo la clase INPUT estatica
// habra que preguntar por un window en particular -puntero glgw a window-

// Engine es global y tiene el Window como propiedad, por lo que window debe proveer 
// una manera de devolver el window nativo o original y poder acceder a el desde 
// el engine global

namespace MHelmet
{
	struct MousePosition
	{
		float x, y;
	};

	enum class CursorState 
	{
		Visible = 0, Hidden, Locked
	};


	class Input
	{
	public:	

		// KeyCode viene de las definiciones propias
		// creadas a proposito para esta aplicacion
		// archivo MHKeyCodes en /deps
		static bool  IsKeyPressed(KeyCode keycode) 
		{ 
			return s_Inst->IsKeyPressed(keycode);
		}

		// MouseButton tambien en MHKeyCodes
		// tal vez no es el sitio mas apropiado para ubicarlo
		static bool  IsMouseButtonPressed(MouseButton button) 
		{
			return s_Inst->IsMouseButtonPressed(button);
		}

		static float GetMouseX() 
		{
			return s_Inst->GetMouseX();
		}

		static float getMouseY() 
		{
			return s_Inst->GetMouseY();
		}

		static MousePosition getMousePos() 
		{
			return s_Inst->GetMousePos();
		}

	protected:

		

		virtual bool  IsKeyPressed(KeyCode keycode) = 0;
		virtual bool  IsMouseButtonPressed(MouseButton button) = 0;
		virtual float GetMouseX() = 0;
		virtual float GetMouseY() = 0;
		virtual MousePosition GetMousePos() = 0;

	private:
		static Input* s_Inst;
	};


}