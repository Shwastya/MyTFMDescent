#pragma once

#include "engine/system/node/NodeLayer.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"
#include "engine/system/events/AppEvents/OnAppEvents.hpp"
#include "engine/system/events/EventSender.hpp"

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

		bool MouseButtonPressed(OnMouseButtonPressed& e);
		bool MouseButtonReleased(OnMouseButtonReleased& e);
		bool MouseMoved(OnMouseMoved& e);
		bool MouseScrolled(OnMouseScrolled& e);
		bool KeyPressed(OnKeyPressed& e);
		bool KeyReleased(OnKeyReleased& e);
		bool KeyTyped(OnKeyTyped& e);
		bool WindowResize(OnWindowResize& e);

		float m_Time = 0.0f;
	};
	
}