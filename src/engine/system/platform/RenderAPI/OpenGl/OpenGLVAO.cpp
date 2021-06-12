#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVAO.hpp"
#include <glad/glad.h>



namespace MHelmet
{
	//using namespace BUFFER;

	/*static GLenum ToOpenGLBaseType(DataType type)
	{
		switch (type)
		{
			case MHelmet::DataType::Float:  return GL_FLOAT;
			case MHelmet::DataType::Float2: return GL_FLOAT;
			case MHelmet::DataType::Float3:	return GL_FLOAT;
			case MHelmet::DataType::Float4:	return GL_FLOAT;
			case MHelmet::DataType::Int:	return GL_INT;
			case MHelmet::DataType::Int2:	return GL_INT;
			case MHelmet::DataType::Int3:	return GL_INT;
			case MHelmet::DataType::Int4:	return GL_INT;
			case MHelmet::DataType::Mat3:	return GL_FLOAT;
			case MHelmet::DataType::Mat4:	return GL_FLOAT;
			case MHelmet::DataType::Bool:	return GL_BOOL;
		}
		return 0;
	}

	OpenGLVAO::OpenGLVAO()
	{
		glDeleteVertexArrays(1, &m_ID_VAO);
	}
	void OpenGLVAO::Bind() const
	{
		glBindVertexArray(m_ID_VAO);
	}
	void OpenGLVAO::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVAO::Add__VBO(PtrVBO& _vbo)
	{
		glBindVertexArray(m_ID_VAO);
		_vbo->Bind();
		
		uint32_t idx = 0;
		auto& layout = _vbo->GetLayout();

		for (const auto& e : layout)
		{
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer
			(
				idx,
				e.ComponentCount(),
				ToOpenGLBaseType(e.Type),
				e.Normalized ? GL_TRUE : GL_FALSE,
				layout.Stride(),
				(const void*)e.Offset
			);
			++idx;
		}

		m_VBOs.push_back(_vbo);
	}


	void OpenGLVAO::Add__EBO(const PtrEBO& _ebo)
	{
		glBindVertexArray(m_ID_VAO);
		_ebo->Bind();

		m_EBO = _ebo;
	}	*/
}