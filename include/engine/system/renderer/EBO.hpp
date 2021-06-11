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

		static EBO* Create(uint32_t* indices, uint32_t size);
	};
}