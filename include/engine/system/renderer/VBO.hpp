#pragma once
#include "engine/system/MHCore.hpp"

namespace MHelmet
{
	class VBO // virtual table of dispatchs clases de puraS funciones
	{
	public:
		virtual ~VBO() {}

		virtual void Bind() const   = 0;
		virtual void Unbind() const = 0;

		static VBO* Create(float* vertices, uint32_t size);


	};
}