#include "engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp"
#include <glad/glad.h>

namespace MHelmet
{
	OpenGLEBO::OpenGLEBO(uint32_t* indices, uint32_t size)
	{
		glGenBuffers(1, &m_ID_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	OpenGLEBO::~OpenGLEBO()
	{
		glDeleteBuffers(1, &m_ID_EBO);
	}

	void OpenGLEBO::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID_EBO);
	}

	void OpenGLEBO::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}