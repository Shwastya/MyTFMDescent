#pragma once
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>
#include <map>

namespace MHelmet
{
	struct FBTextureProps
	{
		
		uint32_t W, H;

		
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:

		virtual ~FrameBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Resize(uint32_t W, uint32_t H) = 0;

		virtual uint32_t GetFBOTexture() const = 0;
		//virtual uint32_t GetDepthTexture() const = 0;
		// get image specifications 
		virtual const FBTextureProps& GetSpecification() const = 0;

		static RefCount<FrameBuffer> Create(const FBTextureProps& spec);
	};
}

