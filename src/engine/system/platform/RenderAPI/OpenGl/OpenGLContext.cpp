#include "engine/system/MHCore.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MH_ENABLE_CORE false

namespace MHelmet
{	OpenGLContext::OpenGLContext(GLFWwindow* _GLFWwindow)
		: m_GLFWwindow(_GLFWwindow)
	{
	}

	void OpenGLContext::Init()
	{
		////////////// OpenGL Contex - BEGIN - //////////////
		if (MH_ENABLE_CORE) // temporal 
		{
			MH_CORE_WARN("OpenGL CORE profile enabled:");
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		glfwMakeContextCurrent(m_GLFWwindow);
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		MH_CORE_ASSERT(result, "Error initializing GLAD!");
		MH_CORE_INFO("OpenGL v.{}", glGetString(GL_VERSION));
		////////////// OpenGL Contex - END -   //////////////
	}

	void OpenGLContext::SwapBuffers()
	{
		glBegin(GL_TRIANGLES);
		glEnd();

		glfwSwapBuffers(m_GLFWwindow);
	}


}