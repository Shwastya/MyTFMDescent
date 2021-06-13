#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/renderer/BufferLayout.hpp"

#include "engine/system/renderer/VBO.hpp"
#include "engine/system/renderer/EBO.hpp"

namespace MHelmet
{	
	//using PtrVBO = std::shared_ptr<VBO>;
	//using PtrEBO = std::shared_ptr<EBO>;

	class VAO // virtual table of dispatchs 
	{
	public:
		virtual ~VAO() = default;

		virtual void Bind() const   = 0;
		virtual void Unbind() const = 0;

		// conteo de referencias
		virtual void Add__VBO(const std::shared_ptr<VBO>& _vbo) = 0;
		// EBO de momento solo tiene capacidad 1, no se cree necesario mas
		virtual void Add__EBO(const std::shared_ptr<EBO>& _ebo) = 0;
		
		virtual const std::vector<std::shared_ptr<VBO>>& GetVBO() const = 0;
		virtual const std::shared_ptr<EBO>& GetEBO() const = 0;

		// FABRICA
		static VAO* Create();

	protected:
		//uint32_t m_ID_VAO[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	};
}