#pragma once

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
#define GLHE_(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))



void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);