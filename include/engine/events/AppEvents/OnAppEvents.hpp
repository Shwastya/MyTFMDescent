#pragma once
#include <sstream>
#include "../Event.hpp"

namespace MHelmet {
	
	struct OnWindowResize : public Event
	{
		OnWindowResize(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) // previous size?
		{ } 

		inline uint32_t GetWidth()  const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		static  inline EventType GetStaticType() { return EventType::E_WINDOW_RESIZE; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }		
		virtual inline int GetCategoryFlags()   const override { return E_CATG_APP; }
		virtual inline std::string Print()	    const override
		{
			std::stringstream ss;			
			ss << "OnWindowResize: " << m_Width + ", " << m_Height;
			return ss.str();
		}

	private:
		uint32_t m_Width, m_Height;
		
	};

	struct OnWindowClose : public Event
	{
		OnWindowClose() {}

		static  inline EventType GetStaticType() { return EventType::E_WINDOW_CLOSE; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }		
		virtual inline int GetCategoryFlags()   const override { return E_CATG_APP; }
		virtual inline std::string Print()	    const override { return "OnWindowClose"; }		
	};

	struct OnAppTick : public Event
	{
		OnAppTick() {}

		static  inline EventType GetStaticType() { return EventType::E_APP_TICK; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }	
		virtual inline int GetCategoryFlags()   const override { return E_CATG_APP; }
		virtual inline std::string Print()	    const override { return "OnAppTick"; }
	};

	struct OnAppUpdate : public Event
	{
		OnAppUpdate() {}

		static  inline EventType GetStaticType() { return EventType::E_APP_UPDATE; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }	
		virtual inline int GetCategoryFlags()   const override { return E_CATG_APP; }
		virtual inline std::string Print()	    const override { return "OnAppUpdate"; }
	};

	struct OnAppRender : public Event
	{
		OnAppRender() {}

		static  inline EventType GetStaticType() { return EventType::E_APP_RENDER; }

		virtual inline EventType GetEventType() const override { return GetStaticType(); }	
		virtual inline int GetCategoryFlags()   const override { return E_CATG_APP; }
		virtual inline std::string Print()	    const override { return "OnAppRender"; }
	};
}