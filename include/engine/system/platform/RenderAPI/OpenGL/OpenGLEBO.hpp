#pragma once

#include "engine/system/renderer/EBO.hpp"

namespace MHelmet
{
	class OpenGLEBO : public EBO
	{
	public:
		OpenGLEBO(uint32_t* indices, uint32_t size);
		virtual ~OpenGLEBO();

		virtual void Bind()   const override;
		virtual void Unbind() const override;

	private:
		//uint32_t m_ID_VAO;
		uint32_t m_ID_EBO;
	};
}