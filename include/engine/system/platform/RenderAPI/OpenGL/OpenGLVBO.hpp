#pragma once

#include "engine/system/renderer/VBO.hpp"

namespace MHelmet 
{
	class OpenGLVBO : public VBO
	{
	public:
		OpenGLVBO(float* vertices, uint32_t size);
		virtual ~OpenGLVBO();

		virtual void Bind()   const override;
		virtual void Unbind() const override;

	private:
		//uint32_t m_ID_VAO;
		uint32_t m_ID_VBO;		
	};
}