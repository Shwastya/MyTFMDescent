#pragma once
#include "engine/system/MHCore.hpp"


namespace MHelmet
{
	struct Texture
	{
		virtual ~Texture() = default;

		virtual uint32_t GetWidth()  const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual uint32_t GetTextureID() const = 0;

		virtual void Bind(uint32_t unit = 0) const = 0;
	};	

	struct Texture2D : public Texture
	{
		enum class Format
		{
			RGB, RGBA
		};

		static RefCount<Texture2D> Create(const std::string& path, Texture2D::Format format);
		static RefCount<Texture2D> Create(uint32_t widh, uint32_t height);
	
	};
}