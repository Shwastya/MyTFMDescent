#include <MHelmet.h>
#include "BrowserPanel.hpp"

namespace MHelmet
{

	static std::filesystem::path s_AssetPath = "../assets";

	ContentBrowserUI::ContentBrowserUI()
		: m_CurrentDirectory(s_AssetPath)
	{
	}

	void ContentBrowserUI::ImGuiRender()
	{
		ImGui::Begin("Browser");
		{
			for (auto& p : std::filesystem::directory_iterator(m_CurrentDirectory))
			{
				std::string path = p.path().string();
				ImGui::Text("%s", path.c_str());
			}
			/*if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
			{
				if (ImGui::Button("<--"))
				{
					m_CurrentDirectory = m_CurrentDirectory.parent_path();
				}
			}
			for (auto& p : std::filesystem::directory_iterator(m_CurrentDirectory))
			{
				const auto& path_ = p.path();
				auto relativePath = std::filesystem::relative(path_, s_AssetPath);
				std::string fileNameString = relativePath.filename().string();
				
			
				if (p.is_directory())
				{
					if (ImGui::Button(fileNameString.c_str()));
					{
						
					}
				}
				else
				{
					if (ImGui::Button(fileNameString.c_str()))
					{

					}
				}
				
				
			}*/
		}
		ImGui::End();

	}
}