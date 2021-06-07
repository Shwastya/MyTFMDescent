#include <MHelmet.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "engine/system/ImGui/ImGuiLayer.hpp"



namespace MHelmet 
{



	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}


	/////////////////////// 
	//  
	//////////////////////
	void ImGuiLayer::Join() 
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	}

	void ImGuiLayer::Free()
	{
	}

	void ImGuiLayer::Update()
	{
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}

}