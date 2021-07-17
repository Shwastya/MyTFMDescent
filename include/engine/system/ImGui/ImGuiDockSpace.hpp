#pragma once

namespace MHelmet
{
	struct ImGuiDockSpace
	{
	
		ImGuiDockSpace() = default;
		void Begin();
		void End();

	private:
		bool m_DocksOpen = true;
	};
}