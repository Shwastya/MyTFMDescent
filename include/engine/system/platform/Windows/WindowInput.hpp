#pragma once

#include "engine/system/Input.hpp"


namespace MHelmet
{
	

	class WindowInput : public Input
	{	
	protected:

	virtual bool  IsKeyPressedImpl(int keycode) override;
	virtual bool  IsMouseButtonPressedImpl(int button) override;
		
	virtual float GetMouseXImpl()	override;
	virtual float GetMouseYImpl()	override;

	virtual MousePos GetMousePosImpl() override;		
	};
}