#pragma once

#include "engine/system/Input.hpp"
#include ""


namespace MHelmet
{
	class WindowInput : public Input
	{	
	protected:

	virtual bool  IsKeyPressed(KeyCode keycode) override;
	virtual bool  IsMouseButtonPressed(MouseButton button) override;
		
	virtual float GetMouseX()	override;
	virtual float GetMouseY()	override;

	virtual MousePosition GetMousePos() override;
	};
}