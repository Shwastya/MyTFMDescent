#pragma once

#include "KeyEvent.hpp"

namespace MHelmet {

	
    ////////////////////////////////////////
    //  OnKeyPressed : KeyEvent : Event   //
    ////////////////////////////////////////

	struct OnKeyPressed : public KeyEvent
	{
		OnKeyPressed(KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline  int GetRepeatCount() const { return m_RepeatCount; }
		static  inline EventType GetStaticType() { return EventType::E_KEY_PRESSED; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }
		virtual inline std::string Print()		const override
		{
			std::stringstream ss;
			ss << "OnKeyPressed: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		
		virtual inline std::string GetName() const override { return "KeyPressed"; }
	private:
		int m_RepeatCount;
	};


    ////////////////////////////////////////
    //  OnKeyReleased : KeyEvent : Event  //
    ////////////////////////////////////////

	struct OnKeyReleased : public KeyEvent
	{
		OnKeyReleased(KeyCode keycode): KeyEvent(keycode) {}		
		static  inline EventType GetStaticType() { return EventType::E_KEY_RELEASED; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }		
		virtual inline std::string Print()		const override
		{
			std::stringstream ss;
			ss << "OnKeyReleased: " << m_KeyCode;
			return ss.str();
		}

		virtual inline std::string GetName() const override { return "KeyReleased"; }
	};


    ////////////////////////////////////////
    //  OnKeyTyped : KeyEvent : Event     //
    ////////////////////////////////////////

	struct OnKeyTyped : public KeyEvent
	{
		OnKeyTyped(KeyCode keycode) : KeyEvent(keycode) {}		
		static  inline EventType GetStaticType() { return EventType::E_KEY_TYPED; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }
		virtual inline std::string Print()		const override
		{
			std::stringstream ss;
			ss << "OnKeyTyped: " << m_KeyCode;
			return ss.str();
		}	

		virtual inline std::string GetName() const override { return "KeyTyped"; }
	};
}