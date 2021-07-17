#pragma once
#include "engine/system/node/NodeLayer.hpp"


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

		void SetMHelmetColors();
	};	
}