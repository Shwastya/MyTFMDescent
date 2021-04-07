#include "engine/system/handleGLerrors.hpp"


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);	
}


bool GLLogCall(const char* function, const char* file, int line)
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