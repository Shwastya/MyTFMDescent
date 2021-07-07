#pragma once

#include "MouseButtonEvent.hpp"

namespace MHelmet
{

    struct OnMouseButtonPressed : public MouseButtonEvent
	{
		OnMouseButtonPressed(int button)
			: MouseButtonEvent(button) {}
		virtual IsType GetEventType() const override { return m_Type; }
	private:
		const static IsType m_Type = IsType::MH_MOUSE_BUTTON_PRESSED;
	};

	struct OnMouseButtonReleased : public MouseButtonEvent
	{
		OnMouseButtonReleased(int button)
			: MouseButtonEvent(button) {}		

		virtual IsType GetEventType() const override { return m_Type; }
	private:
		const static IsType m_Type = IsType::MH_MOUSE_BUTTON_RELEASED;
		
	};

    struct OnMouseMoved : public Event
	{
		OnMouseMoved(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }		

		virtual IsType GetEventType() const override { return m_Type; }

	private:
		float m_MouseX, m_MouseY;
		const static IsType m_Type = IsType::MH_MOUSE_MOVED;
	};


	struct OnMouseScrolled : public Event
	{
		OnMouseScrolled(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		virtual IsType GetEventType() const override { return m_Type; }

	private:
		float m_XOffset, m_YOffset;
		const static IsType m_Type = IsType::MH_MOUSE_SCROLLED;
	};

}