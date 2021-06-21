#pragma once

#include "engine/system/node/NodeLayer.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"
#include "engine/system/events/AppEvents/OnAppEvents.hpp"
#include "engine/system/events/EventSender.hpp"

namespace MHelmet 
{
	

	
	struct ImGuiLayer : public NodeLayer
	{
		ImGuiLayer();
		~ImGuiLayer();

		virtual void Join()   override;
		virtual void Free()   override;

		// darle una personalizacion al comportamiento de las capas de ImGui
		// encerrar en capas su funcionalidad
		void Begin();
		void End();

		//virtual void ImGuiRender() override;
		

	private:

		float m_Time = 0.0f;
	};
	
}