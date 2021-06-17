#pragma once
#include "engine/system/MHCore.hpp"
#include "engine/system/renderer/shader.hpp" 

namespace MHelmet
{
	struct Texture
	{
		virtual ~Texture() = default;

		virtual uint32_t GetWidth()  const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(const RefCount<Shader>& shader, const char* name, uint32_t unit = 0) const = 0;
	};	

	struct Texture2D : public Texture
	{
		enum class Format
		{
			RGB, RGBA
		};

		static RefCount<Texture2D> Create(const std::string& path, Texture2D::Format format);
	};
}