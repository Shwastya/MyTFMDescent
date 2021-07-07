#include "engine/system/platform/RenderAPI/OpenGL/OpenGLFrameBuffer.hpp"
#include "engine/system/MHCore.hpp"
#include <glad/glad.h>
#include "engine/engine.hpp"
#include "engine/system/renderer/RenderDrawCall.hpp"

namespace MHelmet
{

	static void CheckFrameBufferStatus()
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			CORE_ERROR("Error, FrameBuffer Not Complete");
			return;
		}
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FBTextureProps& props)
		: m_TextProps(props), m_TextColor(0), m_RenderBuffer(0), m_FboID(0)
	{
		ColorDepthAttachment();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FboID);
		glDeleteTextures(1, &m_TextColor);
		glDeleteTextures(1, &m_RenderBuffer);
	}
	void OpenGLFrameBuffer::Bind() const
	{
		// PINTA SOBRE EL FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_FboID);
		RenderDrawCall::SetWiewPort(0, 0, m_TextProps.W, m_TextProps.H);
		
	}
	void OpenGLFrameBuffer::Unbind() const
	{
		// DEJA DE PINTAR SOBRE EL FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	void OpenGLFrameBuffer::Resize(uint32_t W, uint32_t H)
	{
		m_TextProps.W = W; 
		m_TextProps.H = H;
		ColorDepthAttachment();
	}
	void OpenGLFrameBuffer::ColorDepthAttachment()
	{
		if (m_FboID) OpenGLFrameBuffer::~OpenGLFrameBuffer();
		// generar el FBO
		glGenFramebuffers(1, &m_FboID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FboID);
		// generar textura color
		glGenTextures(1, &m_TextColor);
		glBindTexture(GL_TEXTURE_2D, m_TextColor);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TextProps.W, m_TextProps.H, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextColor, 0);

		// DEPTH -> usamos la misma textura para el buffer de profundidad hasta mejor idea
		glGenRenderbuffers(1, &m_RenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_TextProps.W, m_TextProps.H);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

		CheckFrameBufferStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);		
	}
}