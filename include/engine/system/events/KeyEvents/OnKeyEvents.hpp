#pragma once

#include "KeyEvent.hpp"

namespace MHelmet 
{
	struct OnKeyPressed : public KeyEvent
	{
		OnKeyPressed(KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return m_RepeatCount; }

		static  IsType GetStaticType() { return IsType::MH_KEY_PRESSED; }
		virtual IsType GetEventType() const override { return GetStaticType(); }
		
	private:

		int m_RepeatCount;
	};

	struct OnKeyReleased : public KeyEvent
	{
		OnKeyReleased(KeyCode keycode): KeyEvent(keycode) {}		

		static  IsType GetStaticType() { return IsType::MH_KEY_RELEASED; }
		virtual IsType GetEventType() const override { return GetStaticType(); }
		
	};

	struct OnKeyTyped : public KeyEvent
	{
		OnKeyTyped(KeyCode keycode) : KeyEvent(keycode) {}		

		static  IsType GetStaticType() { return IsType::MH_KEY_TYPED; }
		virtual IsType GetEventType() const override { return GetStaticType(); }
	};


}