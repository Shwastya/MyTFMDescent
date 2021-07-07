#pragma once
#include "engine/system/node/NodeLayer.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"
#include "engine/system/events/AppEvents/OnAppEvents.hpp"
#include "engine/system/events/EventHandler.hpp"

namespace MHelmet 
{	
	struct ImGuiLayer : public NodeLayer
	{
		ImGuiLayer();
		~ImGuiLayer();

		virtual void Join()   override;
		virtual void Free()   override;
		
		void Begin();
		void End();		

	private:		
		float m_Time = 0.0f;
	};	
}