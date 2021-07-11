#include "engine/system/MHCore.hpp"
#include "engine/system/ImGui/ImGuiLayer.hpp"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "engine/Engine.hpp"

#include <ImGuizmo.h>


namespace MHelmet
{
	ImGuiLayer::ImGuiLayer() : NodeLayer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::Join() 
	{
		
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		//io.FontDefault = io.Fonts->AddFontFromFileTTF("../assets/fonts/Hind_Siliguri/HindSiliguri-Medium.ttf", 18.0f);
		io.Fonts->AddFontFromFileTTF("../assets/fonts/Open_Sans/OpenSans-Bold.ttf", 16.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("../assets/fonts/Open_Sans/OpenSans-Regular.ttf", 16.0f);
		
		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();
		SetMHelmetColors();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;		
		}

		

		// Setup Platform/Renderer bindings
		GLFWwindow* window = static_cast<GLFWwindow*>(Engine::p().GetWindow().GetOriginalWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		const char* glsl_version = "#version 410";
		ImGui_ImplOpenGL3_Init(glsl_version);		
	}

	void ImGuiLayer::Free()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	
	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Engine& engine = Engine::p(); // ptr Engine
		io.DisplaySize = ImVec2
		{
			static_cast<float>(engine.GetWindow().GetWidth()),
			static_cast<float>(engine.GetWindow().GetHeight())
		};

		// Rendering 
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::SetMHelmetColors()
	{
		auto& colors = ImGui::GetStyle().Colors;

		// Tab
		colors[ImGuiCol_Tab]				= ImVec4(0.564f, 0.215f, 0.243f, 1.0f);
		colors[ImGuiCol_TabHovered]			= ImVec4(0.803f, 0.282f, 0.258f, 1.0f);
		colors[ImGuiCol_TabActive]			= ImVec4(0.694f, 0.168f, 0.262f, 1.0f);
		colors[ImGuiCol_TabUnfocused]		= colors[ImGuiCol_Tab];
		colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_Tab];

		// buttons
		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.29f, 0.28f, 1.0f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.39f, 0.38f, 1.0f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.153f, 0.158f, 1.0f);


		// headers
		colors[ImGuiCol_Header]        = colors[ImGuiCol_Button];
		colors[ImGuiCol_HeaderHovered] = colors[ImGuiCol_ButtonHovered];
		colors[ImGuiCol_HeaderActive]  = colors[ImGuiCol_ButtonActive];
		
		

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.305f, 0.31f, 1.0f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.1405f, 0.151f, 1.0f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.1505f, 0.148f, 1.0f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);

		// separator
		colors[ImGuiCol_Separator] = colors[ImGuiCol_TabUnfocused];
		colors[ImGuiCol_SeparatorHovered] = colors[ImGuiCol_TabHovered];
		colors[ImGuiCol_SeparatorActive] = colors[ImGuiCol_TabActive];
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f); 

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

		colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.106f, 0.11f, 1.0f);

		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

		


		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

	

		
		

		


		colors[ImGuiCol_DockingPreview] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		// BACKUP
		//colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		//colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

		//colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.106f, 0.11f, 1.0f);

		//colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		//colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		//colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		//colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

		//// Frame BG
		//colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.209f, 0.28f, 1.0f);
		//colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.309f, 0.38f, 1.0f);
		//colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.1509f, 0.158f, 1.0f);

		//// Titles
		//colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.1405f, 0.151f, 1.0f);
		//colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.1505f, 0.148f, 1.0f);
		//colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);


		//colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		//colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		//colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		//colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		//colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		//colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		//colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		//colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		//// buttons
		//colors[ImGuiCol_Button] = ImVec4(0.26f, 0.29f, 0.28f, 1.0f);
		//colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.39f, 0.38f, 1.0f);
		//colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.153f, 0.158f, 1.0f);

		//// headers
		//colors[ImGuiCol_Header] = ImVec4(0.26f, 0.29f, 0.28f, 1.0f);
		//colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.39f, 0.38f, 1.0f);
		//colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.159f, 0.158f, 1.0f);

		//colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		//colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		//colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		//colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		//colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		//colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

		//// Tab
		//colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
		//colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.3805f, 0.381f, 1.0f);
		//colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.2805f, 0.281f, 1.0f);
		//colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
		//colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);


		//colors[ImGuiCol_DockingPreview] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
		//colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		//colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		//colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		//colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		//colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		//colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		//colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		//colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		//colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		//colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		//colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	/*void ImGuiLayer::ImGuiRender()
	{
		static bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);
	}*/
}