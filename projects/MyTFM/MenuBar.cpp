#include <MHelmet.h>
#include "MenuBar.hpp"

namespace MHelmet
{
	
	void MenuBarUI::ImGuiRender()
	{

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                //ImGui::MenuItem("Padding", NULL, &opt_padding);
                //ImGui::Separator();

                if (ImGui::MenuItem("Exit")) Engine::p().Exit();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
	}
}