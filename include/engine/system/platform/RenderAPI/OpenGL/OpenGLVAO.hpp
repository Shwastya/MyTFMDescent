#pragma once

#include "engine/system/renderer/VAO.hpp"

namespace MHelmet
{
	class OpenGLVAO : public VAO 
	{
	public:

		OpenGLVAO();
		virtual ~OpenGLVAO();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		// conteo de referencias
		virtual void Add__VBO(const std::shared_ptr<VBO>& _vbo) override;
		virtual void Add__EBO(const std::shared_ptr<EBO>& _ebo) override;

		virtual const std::vector<std::shared_ptr<VBO>>& GetVBO() const override { return  m_VBOs; }
		inline
			virtual const std::shared_ptr<EBO>& GetEBO() const override { return m_EBO; }

	private:

		// using std::shared_ptr<Type>
		uint32_t m_ID_VAO;
		std::vector<std::shared_ptr<VBO>> m_VBOs;
		std::shared_ptr<EBO> m_EBO;

	};

}