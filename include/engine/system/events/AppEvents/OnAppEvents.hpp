#pragma once
#include <sstream>
#include "../Event.hpp"

namespace MHelmet {
	
	struct OnWindowResize : public Event
	{
		OnWindowResize(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) // previous size?
		{ } 

		unsigned int GetWidth()  const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		static  IsType GetStaticType() { return IsType::MH_WINDOW_RESIZE; }
		virtual IsType GetEventType() const override { return GetStaticType(); }		
		virtual int GetCategoryFlags()   const override { return MH_CATG_APP; }

	private:
		unsigned int m_Width, m_Height;
		
	};

	struct OnWindowClose : public Event
	{
		OnWindowClose() = default;

		static  IsType GetStaticType() { return IsType::MH_WINDOW_CLOSE; }
		virtual IsType GetEventType() const override { return GetStaticType(); }		
		virtual int GetCategoryFlags()   const override { return MH_CATG_APP; }
	};

	struct OnAppTick : public Event
	{
		OnAppTick() {}

		static  IsType GetStaticType() { return IsType::MH_APP_TICK; }

		virtual IsType GetEventType() const override { return GetStaticType(); }	
		virtual int GetCategoryFlags()   const override { return MH_CATG_APP; }
	};

	struct OnAppUpdate : public Event
	{
		OnAppUpdate() {}

		static  IsType GetStaticType() { return IsType::MH_APP_UPDATE; }

		virtual IsType GetEventType() const override { return GetStaticType(); }	
		virtual int GetCategoryFlags()   const override { return MH_CATG_APP; }
	};

	struct OnAppRender : public Event
	{
		OnAppRender() {}

		static  IsType GetStaticType() { return IsType::MH_APP_RENDER; }

		virtual IsType GetEventType() const override { return GetStaticType(); }
		virtual int GetCategoryFlags()   const override { return MH_CATG_APP; }
	};
}