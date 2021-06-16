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
		virtual void Add__VBO(const RefCount<VBO>& _vbo) override;
		virtual void Add__EBO(const RefCount<EBO>& _ebo) override;

		virtual const std::vector<RefCount<VBO>>& GetVBO() const override { return  m_VBOs; }
		inline
			virtual const RefCount<EBO>& GetEBO() const override { return m_EBO; }

	private:

		// using std::shared_ptr<Type>
		uint32_t m_ID_VAO;
		std::vector<RefCount<VBO>> m_VBOs;
		RefCount<EBO> m_EBO;

	};

}