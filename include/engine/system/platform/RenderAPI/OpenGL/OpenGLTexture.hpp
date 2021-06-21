#pragma once
#include <stb_image.h>
#include "engine/system/renderer/Texture.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"


namespace MHelmet
{
	struct OpenGLTexture2D : public Texture2D
	{	
		enum class Wrap 
		{
			Repeat,
			Mirrored_Repeat,
			Clamp_To_Border,
			Clamp_To_Edge
		};
			
		enum class Filter 
		{
			None,
			Nearest,
			Linear
		};			
	
		OpenGLTexture2D(const std::string& path, Texture2D::Format format);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth()  const override { return m_Width;  };
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void Bind(uint32_t unit) const override;

		virtual void SetData(void* data, uint32_t size) override;
		virtual uint32_t GetTextureID() const override { return m_TextID; }


		void setWrap(Wrap s, Wrap t);
		void setFilter(Filter mag, Filter min, Filter mipMapMag = Filter::None, Filter mipMapMin = Filter::None);

	private:
		void applyWrapping() const;
		void applyFilter() const;
	private:

		const std::string m_Path;

		MHelmet::OpenGLTexture2D::Format m_Format = MHelmet::OpenGLTexture2D::Format::RGB;

		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
		uint32_t m_Depth = 0; // channels

		uint32_t m_TextID;

		std::pair<Wrap, Wrap> m_Wrap
		{ 
			Wrap::Repeat, 
			Wrap::Repeat 
		};
		std::pair<Filter, Filter> m_Filter
		{ 
			Filter::Linear, 
			Filter::Linear 
		};
		std::pair<Filter, Filter> m_FilterMipMap
		{ 
			Filter::None, 
			Filter::None 
		};

		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}