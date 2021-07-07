#include "engine/system/MHCore.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLContext.hpp"

#define MH_ENABLE_CORE true

namespace MHelmet
{	
	
	
	OpenGLContext::OpenGLContext(GLFWwindow* _GLFWwindow)
		: m_GLFWwindow(_GLFWwindow)
	{}

	void OpenGLContext::Init()
	{
		if (MH_ENABLE_CORE) // temporal 
		{			
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);			
		}

		glfwMakeContextCurrent(m_GLFWwindow);
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!result) CORE_ERROR("Error initializing GLAD! {0}:", result);
			
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_GLFWwindow);
	}


}