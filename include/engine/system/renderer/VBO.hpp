#pragma once

#include "engine/system/renderer/BufferLayout.hpp"

namespace MHelmet
{	
	class VBO // virtual table of dispatchs clases de puraS funciones
	{
	public:
		virtual ~VBO() = default;

		virtual void Bind() const   = 0;
		virtual void Unbind() const = 0;

		virtual const BUFFER::Layout& GetLayout() const = 0;
		virtual void SetLayout(const BUFFER::Layout& layout) = 0;
		


		static RefCount<VBO> Create(float* vertices, uint32_t size);


	};
}