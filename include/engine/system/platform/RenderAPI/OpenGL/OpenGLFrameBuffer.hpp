#pragma once
#include "engine/system/renderer/Framebuffer.hpp"

namespace MHelmet
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:

		OpenGLFrameBuffer(const FBProps& spec);
		virtual ~OpenGLFrameBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void ActiveTexture(uint32_t idx) const override;

		virtual void Resize(uint32_t W, uint32_t H) override;

		virtual int ReadPixel(uint32_t attachment, int x, int y) override;

		virtual uint32_t GetFBOTexture(uint32_t idx) const override { return m_Colors[idx]; }
		virtual uint32_t GetDepthBuffer() const override { return m_Depth; }

		virtual const FBProps& GetSpecification() const override { return m_TextProps; };

		void ColorDepthAttachment();

	private:
		uint32_t m_FboID;
		//uint32_t m_TextColor, m_RenderBuffer;



		FBProps m_TextProps;		

		std::vector<FBTextureProps> m_ColorListProps;
		std::vector<uint32_t> m_Colors;

		FBTextureProps m_DepthBufferProp = FBTextureFormat::Depth;
		uint32_t m_Depth = 0;
	}; 
}