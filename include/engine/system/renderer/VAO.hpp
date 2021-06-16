#pragma once

#include "engine/system/renderer/BufferLayout.hpp"

#include "engine/system/renderer/VBO.hpp"
#include "engine/system/renderer/EBO.hpp"

namespace MHelmet
{

	class VAO // virtual table of dispatchs 
	{
	public:
		virtual ~VAO() = default;

		virtual void Bind() const   = 0;
		virtual void Unbind() const = 0;

		// conteo de referencias
		virtual void Add__VBO(const RefCount<VBO>& _vbo) = 0;
		// EBO de momento solo tiene capacidad 1, no se cree necesario mas
		virtual void Add__EBO(const RefCount<EBO>& _ebo) = 0;
		
		virtual const std::vector<RefCount<VBO>>& GetVBO() const = 0;
		virtual const RefCount<EBO>& GetEBO() const = 0;



		static VAO* Create();

	};
}