#pragma once
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

namespace MHelmet
{

	class RendererContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};


} 