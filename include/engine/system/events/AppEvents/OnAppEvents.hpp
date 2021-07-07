#pragma once
#include <sstream>
#include "../Event.hpp"

namespace MHelmet 
{	
	struct OnWindowResize : public Event
	{
		OnWindowResize(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) // previous size?
		{} 

		uint32_t GetWidth()  const { return m_Width;  }
		uint32_t GetHeight() const { return m_Height; }

		virtual IsType GetEventType()  const override { return m_Type; }		

	private:
		uint32_t m_Width, m_Height;	
		const static IsType m_Type = IsType::MH_WINDOW_RESIZE;
	}; 

	struct OnWindowClose : public Event
	{
		OnWindowClose() = default;
		virtual IsType GetEventType() const override { return m_Type; }

	private:
		uint32_t m_Width, m_Height;
		const static IsType m_Type = IsType::MH_WINDOW_CLOSE;

	};
}