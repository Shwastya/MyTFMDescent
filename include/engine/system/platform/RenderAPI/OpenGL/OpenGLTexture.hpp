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
		// MHelmet::OpenGLTexture2D::Format format
		OpenGLTexture2D(const char* path, Texture2D::Format format);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth()  const override { return m_Width;  };
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void Bind(const RefCount<Shader>& shader, const char* name, uint32_t unit) const override;

		void setWrap(Wrap s, Wrap t);
		void setFilter(Filter mag, Filter min, Filter mipMapMag = Filter::None, Filter mipMapMin = Filter::None);

	private:
		void applyWrapping() const;
		void applyFilter() const;
	private:

		char* m_Path;

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
	};
}




//#include <cstdint>
//#include <string>

//class Shader;
//
//class Texture {
//    public:
//        enum class Wrap {
//            Repeat,
//            Mirrored_Repeat,
//            Clamp_To_Border,
//            Clamp_To_Edge
//        };
//
//        enum class Filter {
//            None,
//            Nearest,
//            Linear
//        };
//
//        enum class Format {
//            RGB,   
//            RGBA
//        };
//
//        Texture(const char* path, Format format);
//        Texture() = delete;
//        ~Texture();
//
//        Texture(const Texture&) = default;
//        Texture(Texture&&) = default;
//        Texture& operator=(const Texture&) = default;
//        Texture& operator=(Texture&&) = default;
//
//        void use(const Shader& shader, const char* name, uint32_t unit = 0) const;
//
//        void setWrap(Wrap s, Wrap t);
//        void setFilter(Filter mag, Filter min, Filter mipMapMag = Filter::None, Filter mipMapMin = Filter::None);
//
//    private:
//        void applyWrapping() const;
//        void applyFilter() const;
//
//    private:
//        uint32_t _id = 0;
//        Format _format = Format::RGB;
//        int32_t _width = 0, _height = 0;
//        int32_t _depth = 0;
//        std::pair<Wrap, Wrap>_wrap{ Wrap::Repeat, Wrap::Repeat };
//        std::pair<Filter, Filter>_filter{ Filter::Linear, Filter::Linear };
//        std::pair<Filter, Filter>_filterMipMap{ Filter::None, Filter::None };
//};

