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

		virtual const Layout& GetLayout() const override
		{
			return m_Layout;
		}
		virtual void SetLayout(const Layout& layout) override
		{
			m_Layout = layout;
		}

	private:
		//uint32_t m_ID_VAO;
		uint32_t m_ID_VBO;	
		Layout m_Layout;
	};
}