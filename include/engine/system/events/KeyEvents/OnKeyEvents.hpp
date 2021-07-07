#pragma once

#include "KeyEvent.hpp"

namespace MHelmet 
{
	struct OnKeyPressed : public KeyEvent
	{
		OnKeyPressed(KeyCode keycode, int repeatCount = 1)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return m_RepeatCount; }

		virtual IsType GetEventType() const override { return m_Type; }
		
	private:		
		int m_RepeatCount;
		const static IsType m_Type = IsType::MH_KEY_PRESSED;
	};

	struct OnKeyReleased : public KeyEvent
	{
		OnKeyReleased(KeyCode keycode, int repeat = 1): KeyEvent(keycode), m_RepeatCount(repeat) {}		

		virtual IsType GetEventType() const override { return m_Type; }

	private:
		int m_RepeatCount;
		const static IsType m_Type = IsType::MH_KEY_RELEASED;
		
	};

	struct OnKeyTyped : public KeyEvent
	{
		OnKeyTyped(KeyCode keycode) : KeyEvent(keycode) {}		

		virtual IsType GetEventType() const override {  return m_Type; }

	private:
		const static IsType m_Type = IsType::MH_KEY_TYPED;
	};


}