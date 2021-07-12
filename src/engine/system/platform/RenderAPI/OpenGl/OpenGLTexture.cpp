#include "../src/engine/mhpch.cpp"
#include <glad/glad.h>

#include "engine/system/platform/RenderAPI/OpenGL/OpenGLTexture.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"

namespace MHelmet
{
	static uint32_t format2GL(MHelmet::OpenGLTexture2D::Format format)
	{
		switch (format)
		{
		case MHelmet::OpenGLTexture2D::Format::RGB: return GL_RGB;
		case MHelmet::OpenGLTexture2D::Format::RGBA: return GL_RGBA;
			default:return GL_RGB;
		};
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, Texture2D::Format format)
		: m_Path(path), m_Format(format)
	{
		stbi_set_flip_vertically_on_load(true);

		glGenTextures(1, &m_TextID);
		glBindTexture(GL_TEXTURE_2D, m_TextID);

		applyWrapping();
		applyFilter();

		int32_t width = 0, height = 0, depth = 0;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &depth, 0);

		m_Width  = static_cast<uint32_t>(width);
		m_Height = static_cast<uint32_t>(height);
		m_Depth  = static_cast<uint32_t>(depth);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format2GL(m_Format), m_Width, m_Height, 0, format2GL(m_Format), GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		else
		{
			CORE_ERROR("Failed to Load Texture {0}", path);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// set data directly to GPU
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glGenTextures(1, &m_TextID);
		glBindTexture(GL_TEXTURE_2D, m_TextID);		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextID);		
	}
	void OpenGLTexture2D::Bind(uint32_t unit) const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_TextID);
		
		
	}
	
	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bytesXpixel = m_DataFormat == GL_RGBA ? 4 : 3;
		if (size == m_Width * m_Height * bytesXpixel)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
		}
		else CORE_ERROR("Data must be entire textur");
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	void OpenGLTexture2D::setWrap(Wrap s, Wrap t)
	{
		m_Wrap = std::make_pair(s, t);
		applyWrapping();
	}
	void OpenGLTexture2D::setFilter(Filter mag, Filter min, Filter mipMapMag, Filter mipMapMin)
	{
		m_Filter = std::make_pair(mag, min);
		m_FilterMipMap = std::make_pair(mipMapMag, mipMapMin);
		applyFilter();
	}
	static uint32_t wrap2GL(OpenGLTexture2D::Wrap wrap)
	{
		switch (wrap)
		{
			case OpenGLTexture2D::Wrap::Repeat: return GL_REPEAT;
			case OpenGLTexture2D::Wrap::Mirrored_Repeat: return GL_MIRRORED_REPEAT;
			case OpenGLTexture2D::Wrap::Clamp_To_Border: return GL_CLAMP_TO_BORDER;
			case OpenGLTexture2D::Wrap::Clamp_To_Edge: return GL_CLAMP_TO_EDGE;
			default: return GL_REPEAT;
		};
	}
	void OpenGLTexture2D::applyWrapping() const
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap2GL(m_Wrap.first));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap2GL(m_Wrap.second));
	}
	static uint32_t filter2GL(OpenGLTexture2D::Filter filter, OpenGLTexture2D::Filter mipMap)
	{
		switch (filter) 
		{
			case OpenGLTexture2D::Filter::Nearest: switch (mipMap) 
			{
				case OpenGLTexture2D::Filter::None: return GL_NEAREST;
				case OpenGLTexture2D::Filter::Nearest: return GL_NEAREST_MIPMAP_NEAREST;
				case OpenGLTexture2D::Filter::Linear: return GL_NEAREST_MIPMAP_LINEAR;
				default: return GL_NEAREST;
			};
			case OpenGLTexture2D::Filter::Linear: switch (mipMap) 
			{
				case OpenGLTexture2D::Filter::None: return GL_LINEAR;
				case OpenGLTexture2D::Filter::Nearest: return GL_LINEAR_MIPMAP_NEAREST;
				case OpenGLTexture2D::Filter::Linear: return GL_LINEAR_MIPMAP_LINEAR;
				default: return GL_LINEAR;
			};
			case OpenGLTexture2D::Filter::None:
			default: return GL_NEAREST;
		}
	}

	void OpenGLTexture2D::applyFilter() const 
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter2GL(m_Filter.first, m_FilterMipMap.first));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter2GL(m_Filter.second, m_FilterMipMap.second));
	}	
}