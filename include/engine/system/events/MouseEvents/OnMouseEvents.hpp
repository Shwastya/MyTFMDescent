#pragma once

#include "MouseButtonEvent.hpp"

namespace MHelmet
{
    ////////////////////////////////////////////////////////
    //  OnMouseButtonPressed : MouseButtonEvent : Event   //
    ////////////////////////////////////////////////////////

    struct OnMouseButtonPressed : public MouseButtonEvent
	{
		OnMouseButtonPressed(int button)
			: MouseButtonEvent(button) {}

		
		static  inline EventType GetStaticType() { return EventType::E_MOUSE_BUTTON_PRESSED; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }
		virtual inline std::string Print()		const override
		{
			std::stringstream ss; ss << "MouseButtonPressed: " << m_Button;
			return ss.str();
		}

		virtual inline std::string GetName() const override { return "ButtonPressed"; }
	};

    ////////////////////////////////////////////////////////
    //  OnMouseButtonPressed : MouseButtonEvent : Event   //
    ////////////////////////////////////////////////////////

	struct OnMouseButtonReleased : public MouseButtonEvent
	{
		OnMouseButtonReleased(int button)
			: MouseButtonEvent(button) {}		

		static  inline EventType GetStaticType() { return EventType::E_MOUSE_BUTTON_RELEASED; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }
		virtual inline std::string Print()		const override
		{
			std::stringstream ss; 
			ss << "MouseButtonReleased: " << m_Button;
			return ss.str();
		}		

		virtual inline std::string GetName() const override { return "ButtonReleased"; }
	};

    ////////////////////////////////
    //  OnMouseMoved : Event      //
    ////////////////////////////////

    struct OnMouseMoved : public Event
	{
		OnMouseMoved(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }		

		static  inline EventType GetStaticType() { return EventType::E_MOUSE_MOVED; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }
		inline virtual int GetCategoryFlags()   const override { return E_CATG_MOUSE | E_CATG_INPUT; }
		virtual inline std::string Print()      const override
		{
			std::stringstream ss;
			ss << "MouseMoved: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		virtual inline std::string GetName() const override { return "MouseMoved"; }

	private:
		float m_MouseX, m_MouseY;
	};

    ////////////////////////////////
    //  OnMouseScrolled : Event   //
    ////////////////////////////////

	struct OnMouseScrolled : public Event
	{
		OnMouseScrolled(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		
		static  inline EventType GetStaticType() { return EventType::E_MOUSE_SCROLLED; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }			
		inline virtual int GetCategoryFlags()	const override { return E_CATG_MOUSE | E_CATG_INPUT; }
		virtual inline std::string Print()		const override
		{
			std::stringstream ss;
			ss << "MouseScrolled: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		virtual inline std::string GetName() const override { return "MouseScrolled"; }
	private:
		float m_XOffset, m_YOffset;
	};

}