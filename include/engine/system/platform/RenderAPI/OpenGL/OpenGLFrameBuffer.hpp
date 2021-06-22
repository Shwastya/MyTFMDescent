#pragma once
#include "engine/system/renderer/Framebuffer.hpp"

namespace MHelmet
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:

		OpenGLFrameBuffer(const FBTextureProps& textureProps);
		virtual ~OpenGLFrameBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void Resize(uint32_t W, uint32_t H) override;

		virtual uint32_t GetFBOTexture() const override { return m_TextColor; }
		//virtual uint32_t GetDepthTexture() const override { return m_TextDepth; }

		virtual const FBTextureProps& GetSpecification() const override { return m_TextProps; };

		void ColorDepthAttachment();

	private:
		uint32_t m_FboID;
		uint32_t m_TextColor;
		uint32_t m_RenderBuffer;
		FBTextureProps m_TextProps;
	};
}