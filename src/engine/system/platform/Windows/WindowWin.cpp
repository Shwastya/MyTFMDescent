#include "../src/engine/mhpch.cpp"

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include "engine/system/platform/windows/WindowWin.hpp"
#include "engine/system/events/AppEvents/OnAppEvents.hpp"
#include "engine/system/events/KeyEvents/OnKeyEvents.hpp"
#include "engine/system/events/MouseEvents/OnMouseEvents.hpp"

#include "engine/system/platform/RenderAPI/OpenGL/OpenGLContext.hpp"

namespace MHelmet 
{
	static bool s_GLFW_ON = false;
	static void GLFWErrorCallback(int error, const char* description)
	{	
		CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}	

	/************************************************/
	Window* Window::Create(const WindowSpec& spec) 
	{
		return new WindowWin(spec);
	}
	WindowWin::WindowWin(const WindowSpec& spec)
		: m_Spec(spec)	
	{ 
		Init(); 
	}
	/************************************************/

	WindowWin::~WindowWin() { ShutDown(); }

	void WindowWin::Init()
	{
		m_Data.Title = m_Spec.Title;
		m_Data.Size  = m_Spec.Size;		

		CORE_INFO("CREATED WINDOW {0} {1} {2}: ", m_Spec.Title, m_Spec.Size.Width, m_Spec.Size.Height);

		if (!s_GLFW_ON) // window context render initialized
		{
			int success = glfwInit();

			if (!success) CORE_ERROR("Error initializing GLFW! {0}: ", success);			

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFW_ON = true;
		}

		if (m_Spec.FullScreen)
		{
			// NOTAS:
			// glfwGetPrimaryMonitor() -> devuelve el monitor primario de tu sistema
			// GLFWmonitor -> opaque monitor object
			// GLFWmonitor** glfwGetMonitors(int* count) // array de monitores conectados
			
			GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* m = glfwGetVideoMode(PrimaryMonitor);

			m_Window = glfwCreateWindow(m->width, m->height, m_Data.Title.c_str() , PrimaryMonitor, nullptr);
		
			
		}
		else 
		{
				m_Window = glfwCreateWindow(
				static_cast<int>(m_Spec.Size.Width), 
				static_cast<int>(m_Spec.Size.Height), 
				m_Data.Title.c_str(), nullptr, nullptr
				);
				
		}		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		
			
		/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);			
	
		glfwMakeContextCurrent(m_Window);    
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);*/
		////////////// OpenGL Contex - END -   //////////////	
		

		// Puntero a la instancia actual del window
		glfwSetWindowUserPointer(m_Window, &m_Data);


		/*********************************************************/
		/*                   GLFW callbacks set                  */
		/*********************************************************/
		#define WD_CAST reinterpret_cast<WindowData*>

		/// On Window Close
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			auto& data = *(WD_CAST(glfwGetWindowUserPointer(window)));

			OnWindowClose event;
			data.CallBack(event);
		});

		/// On Window Resize
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *(WD_CAST(glfwGetWindowUserPointer(window)));

			OnWindowResize event
			(
				static_cast<uint32_t>(width), 
				static_cast<uint32_t>(height)
			);

			data.CallBack(event);
			data.Size.Width  = width;
			data.Size.Height = height;
		});

		/// On Set key
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *(WD_CAST(glfwGetWindowUserPointer(window)));

			switch (action)
			{
				case GLFW_PRESS:
				{
					OnKeyPressed event((KeyCode)key, 0);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					OnKeyReleased event((KeyCode)key);
					data.CallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					OnKeyPressed event((KeyCode)key, 1);
					data.CallBack(event);
					break;
				}
			}
		});

		/// On Set Char
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t codepoint)
		{
			auto& data = *(WD_CAST(glfwGetWindowUserPointer(window)));

			OnKeyTyped event((KeyCode)codepoint);
			data.CallBack(event);
		});

		/// On Mouse Button
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& data = *(WD_CAST(glfwGetWindowUserPointer(window)));

			switch (action)
			{
				case GLFW_PRESS:
				{
					OnMouseButtonPressed event(button);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					OnMouseButtonReleased event(button);
					data.CallBack(event);
					break;
				}
			}
		});

		/// On Mouse Scroll
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *(WD_CAST(glfwGetWindowUserPointer(window)));

			OnMouseScrolled event(
				static_cast<float>(xOffset), 
				static_cast<float>(yOffset)
			);

			data.CallBack(event);
		});

		/// On Set Cursor Position
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			auto& data = *(WD_CAST(glfwGetWindowUserPointer(window)));
			OnMouseMoved event
			(
				static_cast<float>(x), 
				static_cast<float>(y)
			);
			data.CallBack(event);
		});
	}

	//void WindowWin::SwapBuffers() 
	void WindowWin::SwapBuffers()
	{
		glfwPollEvents();

		glfwSwapBuffers(m_Window);
		
		// cambio de contexto de render sin implementar nada
		// solo puntero
		//m_Context->SwapBuffers(); 
	}

	Position WindowWin::GetPos() const
	{
		int x, y;
		glfwGetWindowPos(m_Window, &x, &y);
		const Position position = {x, y};
		return position; // copy ellision
	}

	void WindowWin::Maximize()
	{
		glfwMaximizeWindow(m_Window);
	}	

	void WindowWin::SetVSync(bool toggle)
	{
		if (toggle) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = toggle;
	}

	void WindowWin::SetCaptureMode(bool toggle) const
	{
		if (toggle)	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		else glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);		
	}

	void WindowWin::ShutDown()
	{
		s_GLFW_ON = false;
		glfwTerminate();					
	}
}