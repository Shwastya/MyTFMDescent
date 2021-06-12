#pragma once
#include "engine/system/MHCore.hpp"

namespace MHelmet
{	
	class EBO
	{
	public:
		virtual ~EBO() {}

		virtual void Bind() const   = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t Count() const = 0;

		std::shared_ptr<EBO> Create(uint32_t* indices, uint32_t n_indices);
	};
}