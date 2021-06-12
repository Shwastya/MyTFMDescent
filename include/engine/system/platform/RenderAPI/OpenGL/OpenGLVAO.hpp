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
		virtual void Add__VBO(const PtrVBO& _vbo) override;
		virtual void Add__EBO(const PtrEBO& _ebo) override;

		inline
			virtual const std::vector<PtrVBO>& GetVBO() const override { return  m_VBOs; }
		inline
			virtual const PtrEBO& GetEBO() const override { return m_EBO; }

	private:

		// using std::shared_ptr<Type>
		uint32_t m_ID_VAO;
		std::vector<PtrVBO> m_VBOs;
		PtrEBO m_EBO;

	};

}