#pragma once

#include "MouseButtonEvent.hpp"

namespace MHelmet
{

    struct OnMouseButtonPressed : public MouseButtonEvent
	{
		OnMouseButtonPressed(int button)
			: MouseButtonEvent(button) {}

		
		static  IsType GetStaticType() { return IsType::MH_MOUSE_BUTTON_PRESSED; }
		virtual IsType GetEventType() const override { return GetStaticType(); }
	};

	struct OnMouseButtonReleased : public MouseButtonEvent
	{
		OnMouseButtonReleased(int button)
			: MouseButtonEvent(button) {}		

		static  IsType GetStaticType() { return IsType::MH_MOUSE_BUTTON_RELEASED; }
		virtual IsType GetEventType() const override { return GetStaticType(); }
		
	};

    struct OnMouseMoved : public Event
	{
		OnMouseMoved(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }		

		static  IsType GetStaticType() { return IsType::MH_MOUSE_MOVED; }
		virtual IsType GetEventType() const override { return GetStaticType(); }
		virtual int GetCategoryFlags()   const override { return MH_CATG_MOUSE | MH_CATG_INPUT; }		

	private:
		float m_MouseX, m_MouseY;
	};


	struct OnMouseScrolled : public Event
	{
		OnMouseScrolled(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		
		static  IsType GetStaticType() { return IsType::MH_MOUSE_SCROLLED; }
		virtual IsType GetEventType() const override { return GetStaticType(); }			
		virtual int GetCategoryFlags()	const override { return MH_CATG_MOUSE | MH_CATG_INPUT; }

	private:
		float m_XOffset, m_YOffset;
	};

}