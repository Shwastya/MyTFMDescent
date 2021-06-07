#pragma once

#include "engine/system/node/NodeLayer.hpp"


namespace MHelmet 
{
	using Layer = NodeLayer;

	
	struct ImGuiLayer : public Layer
	{
		ImGuiLayer();
		~ImGuiLayer();

		void Join();
		void Free();

		void Update();
		void OnEvent(Event& event);

	private:
	};
	
}