#pragma once
// INPUT POLLIN - STATIC  GLOBAL MANAGER


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
	struct MousePos
	{
		float x, y;
	};
	class Input
	{
	public:
		

		static bool  IsKeyPressed(int keycode) { 
			return s_Inst->IsKeyPressedImpl(keycode);}

		static bool  IsMouseButtonPressed(int button) {
			return s_Inst->IsMouseButtonPressedImpl(button);}

		static float GetMouseX() {
			return s_Inst->GetMouseXImpl();}

		static float getMouseY() {
			return s_Inst->GetMouseYImpl();}

		static MousePos getMousePos() {
			return s_Inst->GetMousePosImpl();
		}

	protected:

		

		virtual bool  IsKeyPressedImpl(int keycode) = 0;
		virtual bool  IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual MousePos  GetMousePosImpl() = 0;

	private:
		static Input* s_Inst;
	};


}