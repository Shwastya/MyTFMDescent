#pragma once
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>
#include <map>

namespace MHelmet
{
	enum class FBTextureFormat // Frame Buffer Texture Format
	{
		NONE = 0,
		// color
		RGBA8,
		RGB,
		REDINTEGER,

		// depth & stencil
		DEPTH24STENCIL8,
		DEPTHCOMPONENT24,

		// default
		Depth = DEPTHCOMPONENT24
	};

	struct FBTextureProps // Frame Buffer Texture specification
	{
		FBTextureProps() = default;
		FBTextureProps(FBTextureFormat format)
			: TextureFormat(format) {}

		FBTextureFormat TextureFormat = FBTextureFormat::NONE;
	};

	struct FBPropCollection
	{
		FBPropCollection() = default;
		FBPropCollection(std::initializer_list<FBTextureProps> list)
			: Collection(list) {}
		std::vector<FBTextureProps> Collection;
	};

	struct FBProps  // Frame Buffer specifications
	{
		
		uint32_t W, H;		

		FBPropCollection List;

		uint32_t Samples = 1;
	};

	

	class FrameBuffer
	{
	public:

		virtual ~FrameBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void ActiveTexture(uint32_t idx) const = 0;

		virtual void Resize(uint32_t W, uint32_t H) = 0;


		virtual int ReadPixel(uint32_t attachment, int x, int y) = 0;

		virtual uint32_t GetFBOTexture(uint32_t idx = 0) const = 0;
		virtual uint32_t GetDepthBuffer() const = 0;
		// get image specifications 
		virtual const FBProps& GetSpecification() const = 0;

		static RefCount<FrameBuffer> Create(const FBProps& spec);
	};
}

