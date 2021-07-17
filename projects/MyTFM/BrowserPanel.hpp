#pragma once
#include <filesystem>
namespace MHelmet
{
	class ContentBrowserUI
	{
	public:

		ContentBrowserUI();

		void ImGuiRender();

	private:

		std::filesystem::path m_CurrentDirectory;
	};


}