#pragma once
#include "engine/system/renderer/RendererContext.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MHelmet
{

	class OpenGLContext : public RendererContext
	{
	public:

		OpenGLContext(GLFWwindow* _GLFWwindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_GLFWwindow;
	};
}