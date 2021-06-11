#pragma once

#include "engine/system/renderer/EBO.hpp"

namespace MHelmet
{
	class OpenGLEBO : public EBO
	{
	public:
		OpenGLEBO(uint32_t* indices, uint32_t  n_indices);
		virtual ~OpenGLEBO();

		virtual void Bind()   const override;
		virtual void Unbind() const override;

		inline virtual uint32_t Count() const override
		{
			return m_IndicesCount;
		}

	private:
		
		uint32_t m_ID_EBO;
		uint32_t m_IndicesCount;
	};
}