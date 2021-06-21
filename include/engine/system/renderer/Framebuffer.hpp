#pragma once
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>
#include <map>

namespace MHelmet
{
	struct FBTextureProps
	{
		//FBTextureProps() = default;
		
		uint32_t Width, Height;

		// Framebuffer
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:

		virtual ~FrameBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		// get image specifications 
		virtual const FBTextureProps& GetSpecification() const = 0;

		static RefCount<FrameBuffer> Create(const FBTextureProps& spec);
	};
}

