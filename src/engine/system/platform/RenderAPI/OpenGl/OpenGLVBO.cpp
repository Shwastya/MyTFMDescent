#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVBO.hpp"
#include <glad/glad.h>

namespace MHelmet 
{
	OpenGLVBO::OpenGLVBO(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_ID_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID_VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVBO::~OpenGLVBO()
	{
		glDeleteBuffers(1, &m_ID_VBO);
	}

	void OpenGLVBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID_VBO);
	}

	void OpenGLVBO::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}