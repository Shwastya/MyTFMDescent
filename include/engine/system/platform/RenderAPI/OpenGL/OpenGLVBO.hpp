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

		inline virtual const SHADER::Layout& GetLayout() const override
		{
			return m_Layout;
		}
		inline virtual void SetLayout(const SHADER::Layout& layout) override
		{
			m_Layout = layout;
		}

	private:
		//uint32_t m_ID_VAO;
		uint32_t m_ID_VBO;	
		SHADER::Layout m_Layout;
	};
}