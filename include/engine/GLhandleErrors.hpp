#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifdef _MSC_VER
	#define ASSERT(x) if (!(x)) __debugbreak()
#endif
#ifdef __linux__
	#include <signal.h>
	#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#endif
// GLHE (GL Handle Errors)
#define GLHE_(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))



static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);	
}


static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::string showError;

		switch (error)
		{
			case GL_INVALID_ENUM:      showError = "INVALID_ENUM";      break;
			case GL_INVALID_VALUE:     showError = "INVALID_VALUE";     break;
			case GL_INVALID_OPERATION: showError = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:    showError = "STACK_OVERFLOW";    break;
			case GL_STACK_UNDERFLOW:   showError = "STACK_UNDERFLOW";   break;
			case GL_OUT_OF_MEMORY:		showError = "OUT_OF_MEMORY";		break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
												showError = "INVALID_FRAMEBUFFER_OPERATION";
			break;
		}

		std::cout << "[ OpenGL Error ] (" << error << "): " << showError << std::endl;
		std::cout << "[ File         ] " << file << std::endl;
		std::cout << "[ At line      ] " << line  << ": " << function  << std::endl;
		
		return false;
	}
	return true;
}