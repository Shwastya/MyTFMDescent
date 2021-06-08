#include <MHelmet.h>
#include "engine/system/ImGui/ImGuiLayer.hpp"



#include <imgui.h>
#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>
#include "engine/system/ImGui/imgui_hack_opengl3.h"


#include <GLFW/glfw3.h>



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


		ImGuiIO& io = ImGui::GetIO();

		// standar ImGui setup
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Keyboard mapping. Dear ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		// ImGui_ImplOpenGL3_Init("#version 410");
		const char* glsl_version = "#version 410";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void ImGuiLayer::Free()
	{
	}

	void ImGuiLayer::Update()
	{

		ImGuiIO& io = ImGui::GetIO();
		Engine& app = Engine::p();
		
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		//ImGui_ImplGlfw_InitForOpenGL(app.GetWindow(), true);
		// TIMING
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;


		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();		
		ImGui::NewFrame();
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
	/*	ImGui::ShowDemoWindow();
		ImGui::End();*/
		//// rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		PerformEvent perform(e);
		
		perform.DoTask<OnMouseButtonPressed>
		(
			BINDIMGUIEVENT(MouseButtonPressed)
		);

		perform.DoTask<OnMouseButtonReleased>
		(
			BINDIMGUIEVENT(MouseButtonReleased)
		);

		perform.DoTask<OnMouseMoved>
		(
			BINDIMGUIEVENT(MouseMoved)
		);

		perform.DoTask<OnMouseScrolled>
		(
			BINDIMGUIEVENT(MouseScrolled)
		);

		perform.DoTask<OnKeyPressed>
		(
			BINDIMGUIEVENT(KeyPressed)
		);
		perform.DoTask<OnKeyTyped>
		(
			BINDIMGUIEVENT(KeyTyped)
		);
		perform.DoTask<OnKeyReleased>
		(
			BINDIMGUIEVENT(KeyReleased)
		);

		perform.DoTask<OnWindowResize>
		(
			BINDIMGUIEVENT(WindowResize)
		);
	}

	bool ImGuiLayer::MouseButtonPressed(OnMouseButtonPressed& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::MouseButtonReleased(OnMouseButtonReleased& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::MouseMoved(OnMouseMoved& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::MouseScrolled(OnMouseScrolled& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::KeyPressed(OnKeyPressed& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		//io.KeysDown[e.GetKeyCode()] = true;
		
		io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]	 || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::KeyReleased(OnKeyReleased& e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	bool ImGuiLayer::KeyTyped(OnKeyTyped& e)
	{
		//ImGuiIO& io = ImGui::GetIO();
	//	int keycode = e.GetKeyCode();
	//	if (c > 0 && c < 0x10000)
		//	io.AddInputCharacter((unsigned short)c);
		return false;
	}

	bool ImGuiLayer::WindowResize(OnWindowResize& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

}