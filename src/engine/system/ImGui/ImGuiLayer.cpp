#include "engine/system/MHCore.hpp"
#include "engine/system/ImGui/ImGuiLayer.hpp"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include "engine/Engine.hpp"

// temporal
//#include <GLFW/glfw3.h>
//#include <glad/glad.h>



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

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

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

	/*void ImGuiLayer::ImGuiRender()
	{
		static bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);
	}*/
}