#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVAO.hpp"
#include <glad/glad.h>
#include "engine/system/MHCore.hpp"

namespace MHelmet
{
	static GLenum ToOpenGLBaseType(BUFFER::DataType type)
	{
		switch (type)
		{
			case MHelmet::BUFFER::DataType::Float:  return GL_FLOAT;
			case MHelmet::BUFFER::DataType::Float2: return GL_FLOAT;
			case MHelmet::BUFFER::DataType::Float3:	return GL_FLOAT;
			case MHelmet::BUFFER::DataType::Float4:	return GL_FLOAT;
			case MHelmet::BUFFER::DataType::Int:	return GL_INT;
			case MHelmet::BUFFER::DataType::Int2:	return GL_INT;
			case MHelmet::BUFFER::DataType::Int3:	return GL_INT;
			case MHelmet::BUFFER::DataType::Int4:	return GL_INT;
			case MHelmet::BUFFER::DataType::Mat3:	return GL_FLOAT;
			case MHelmet::BUFFER::DataType::Mat4:	return GL_FLOAT;
			case MHelmet::BUFFER::DataType::Bool:	return GL_BOOL;
		}
		return 0;
	}

	OpenGLVAO::OpenGLVAO()
	{
		glGenVertexArrays(1, &m_ID_VAO);
	}
	OpenGLVAO::~OpenGLVAO()
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
	void OpenGLVAO::Add__VBO(const std::shared_ptr<VBO>& _vbo)
	{

		// CAMBIAR POR ASSERT CON MACRO Y LOG 
		if (_vbo->GetLayout().GetElements().size() < 1)
		{
			MH_CORE_ERROR("VBO layout not found");
			__debugbreak;
		}

		glBindVertexArray(m_ID_VAO);
		_vbo->Bind();

		uint32_t idx = 0;

		const auto& layout   = _vbo->GetLayout();		
		const auto& elements = layout.GetElements();

		for (int i = 0; i < elements.size(); i++)
		{
			MH_CORE_INFO("BUFFER LAYOUT IS WORKING!! {0} ", i);
			glEnableVertexAttribArray(idx);

			glVertexAttribPointer
			(				
				idx,
				elements[i].ComponentCount(),
				ToOpenGLBaseType(elements[i].Type),
				elements[i].Normalized ? GL_TRUE : GL_FALSE,
				layout.Stride(),
				(const void*)elements[i].Offset
			);

			++idx;
		}

		m_VBOs.push_back(_vbo);
	}


	void OpenGLVAO::Add__EBO(const std::shared_ptr<EBO>& _ebo)
	{
		glBindVertexArray(m_ID_VAO);
		_ebo->Bind();

		m_EBO = _ebo;
	}	
}