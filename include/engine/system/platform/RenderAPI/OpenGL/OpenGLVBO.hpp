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

		virtual const BUFFER::Layout& GetLayout() const override
		{
			return m_Layout;
		}
		virtual void SetLayout(const BUFFER::Layout& layout) override
		{
			m_Layout = layout;
		}

	
		

	private:
		//uint32_t m_ID_VAO;
		uint32_t m_ID_VBO;	
		BUFFER::Layout m_Layout;
	};
}