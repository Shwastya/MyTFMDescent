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

	OpenGLTexture2D::OpenGLTexture2D(const char* path, Texture2D::Format format) 
		: m_Format(format)
	{

		// guardo el path por si necesitara recargar la textura
		const size_t size = strlen(path);
		m_Path = new char[size + 1];
		memcpy(m_Path, path, size);
		m_Path[size] = 0;


		stbi_set_flip_vertically_on_load(true);

		glGenTextures(1, &m_TextID);
		glBindTexture(GL_TEXTURE_2D, m_TextID);

		applyWrapping();
		applyFilter();

		int32_t width = 0, height = 0, depth = 0;
		unsigned char* data = stbi_load(path, &width, &height, &depth, 0);

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
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		//delete[] m_Path;
		glDeleteTextures(1, &m_TextID);		
	}
	void OpenGLTexture2D::Bind(const RefCount<Shader>& shader, const char* name, uint32_t unit) const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_TextID);
		
		std::reinterpret_pointer_cast<OpenGLShader>(shader)->SetUniform(name, static_cast<int32_t>(unit));
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap2GL(m_Wrap.second));
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

//static uint32_t format2GL(Texture::Format format) {
//    switch (format) {
//    case Texture::Format::RGB: return GL_RGB;
//    case Texture::Format::RGBA: return GL_RGBA;
//    default:return GL_RGB;
//    };
//}
//
//Texture::Texture(const char* path, Format format) : _format(format) {
//    stbi_set_flip_vertically_on_load(true);
//
//    glGenTextures(1, &_id);
//    glBindTexture(GL_TEXTURE_2D, _id);
//
//    applyWrapping();
//    applyFilter();
//
//    unsigned char* data = stbi_load(path, &_width, &_height, &_depth, 0);
//    if (data) {
//        glTexImage2D(GL_TEXTURE_2D, 0, format2GL(_format), _width, _height, 0, format2GL(_format), GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//        stbi_image_free(data);
//    } else {
//        std::cout << "Failed to Load Texture " << path << std::endl;
//    }
//
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//Texture::~Texture() {
//    glDeleteTextures(1, &_id);
//}
//
//void Texture::setWrap(Wrap s, Wrap t) {
//    _wrap = std::make_pair(s, t);
//    applyWrapping();
//}
//
//void Texture::setFilter(Filter mag, Filter min, Filter mipMapMag, Filter mipMapMin) {
//    _filter = std::make_pair(mag, min);
//    _filterMipMap = std::make_pair(mipMapMag, mipMapMin);
//    applyFilter();
//}
//
//static uint32_t wrap2GL(Texture::Wrap wrap) {
//    switch (wrap) {
//        case Texture::Wrap::Repeat: return GL_REPEAT;
//        case Texture::Wrap::Mirrored_Repeat: return GL_MIRRORED_REPEAT;
//        case Texture::Wrap::Clamp_To_Border: return GL_CLAMP_TO_BORDER;
//        case Texture::Wrap::Clamp_To_Edge: return GL_CLAMP_TO_EDGE;
//        default: return GL_REPEAT;
//    };
//}
//
//void Texture::applyWrapping() const {
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap2GL(_wrap.first));
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap2GL(_wrap.second));
//}
//
//static uint32_t filter2GL(Texture::Filter filter, Texture::Filter mipMap) {
//    switch (filter) {
//        case Texture::Filter::Nearest: switch (mipMap) {
//            case Texture::Filter::None: return GL_NEAREST;
//            case Texture::Filter::Nearest: return GL_NEAREST_MIPMAP_NEAREST;
//            case Texture::Filter::Linear: return GL_NEAREST_MIPMAP_LINEAR;
//            default: return GL_NEAREST;
//        };
//        case Texture::Filter::Linear: switch (mipMap) {
//            case Texture::Filter::None: return GL_LINEAR;
//            case Texture::Filter::Nearest: return GL_LINEAR_MIPMAP_NEAREST;
//            case Texture::Filter::Linear: return GL_LINEAR_MIPMAP_LINEAR;
//            default: return GL_LINEAR;
//        };
//        case Texture::Filter::None:
//        default: return GL_NEAREST;
//    }
//}
//
//void Texture::applyFilter() const {
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter2GL(_filter.first, _filterMipMap.first));
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter2GL(_filter.second, _filterMipMap.second));
//}
//
//void Texture::use(const Shader& shader, const char* name, uint32_t unit) const {
//    glActiveTexture(GL_TEXTURE0 + unit);
//    glBindTexture(GL_TEXTURE_2D, _id);
//   // shader.set(name, static_cast<int32_t>(unit));
//}