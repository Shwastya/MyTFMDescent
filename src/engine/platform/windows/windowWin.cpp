#include <MHpch.h>
#include <glad/glad.h>
#include "engine/platform/windows/WindowWin.hpp"

namespace MHelmet {

	static void GLFWErrorCallback(int error, const char* description)
	{
		MH_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	static bool s_GLFWInitialized = false;

	/*********************************************/

	Window* Window::Create(const WindowSpec& spec)
	{
		return new WindowWin(spec);
	}

	WindowWin::WindowWin(const WindowSpec& spec)
		: m_Spec(spec)	{}

	/**********************************************/

	WindowWin::~WindowWin() { ShutDown(); }

	void WindowWin::Init()
	{
		m_Data.Title = m_Spec.Title;
		m_Data.Size  = m_Spec.Size;

		MH_CORE_INFO("Created window {0} {1} {2}", m_Spec.Title, m_Spec.Size.Width, m_Spec.Size.Height);

		if (!s_GLFWInitialized) // window context render initialized
		{
			int success = glfwInit();
			

			MH_CORE_ASSERT(success, "Error initializing GLFW");

			glfwSetErrorCallback(GLFWErrorCallback);
			
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			s_GLFWInitialized = true;
		}

		if (!m_Spec.FullScreen)
		{
			m_Window = glfwCreateWindow(m_Spec.Size.Width, m_Spec.Size.Width, m_Data.Title, nullptr, nullptr);
		}
		else 
		{
			// glfwGetPrimaryMonitor() -> devuelve el monitor primario de tu sistema
			// GLFWmonitor -> opaque monitor object
			// GLFWmonitor** glfwGetMonitors(int* count) // array de monitores conectados
			GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* m = glfwGetVideoMode(PrimaryMonitor);

			m_Window = glfwCreateWindow(m->width, m->height, m_Data.Title, nullptr, nullptr);
		}





	}

	

	void WindowWin::ShutDown() 
	{
		s_GLFWInitialized = false;
		glfwTerminate();		
	}
}