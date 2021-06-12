#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/renderer/BufferLayout.hpp"

namespace MHelmet
{	
	class VBO // virtual table of dispatchs clases de puraS funciones
	{
	public:
		virtual ~VBO() {}

		virtual void Bind() const   = 0;
		virtual void Unbind() const = 0;

		virtual const BUFFER::Layout& GetLayout() const = 0;
		virtual void SetLayout(const BUFFER::Layout& layout) = 0;
		


		static std::unique_ptr<VBO> Create(float* vertices, uint32_t size);


	};
}