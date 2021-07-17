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



	// create a namespace o clase especifica
	/*********/
	static GLenum TextureTarget(bool samples)      
	{	
		return samples ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D; 
	}
	static GLenum RenderBufferTarget(bool samples) { return samples ? GL_RENDERBUFFER_SAMPLES : GL_RENDERBUFFER; }
	/*********/
	/*********/
	static void CreateColorTexture(uint32_t* outID, uint32_t count)	
	{ 
		glGenTextures(count, outID); 
	}
	static void CreateRenderBuffer(uint32_t* outID, uint32_t count)
	{ 
		glGenRenderbuffers(count, outID);	
	}
	/*********/
	/*********/  
	static void BindTexture(bool samples, uint32_t id)	   
	{ 
		//glBindTexture(TextureTarget(samples), id); 
		glBindTexture(TextureTarget(samples), id);
	}
	static void BinRenderBuffer(bool samples, uint32_t id)	
	{ 
		glBindRenderbuffer(RenderBufferTarget(samples), id); 
	}
	/*********/
	/*********/
	static void AttachTexture(uint32_t id, int samples, GLenum interanlformat, GLenum format, uint32_t w, uint32_t h, int idx)
	{
		
		bool multisampled = samples > 1;
		if (multisampled)			
		{			
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, interanlformat, w, h, GL_FALSE);
		}
		else
		{
			
			glTexImage2D(GL_TEXTURE_2D, 0, interanlformat, w, h, 0, format, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, 0);
			
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + idx, TextureTarget(multisampled), id, 0);
	}
	static void AttachRenderBuffer(uint32_t id, int samples, GLenum format, GLenum atachmentType, uint32_t W, uint32_t H)
	{
		bool multisampled = samples > 1;

		if (multisampled)
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER_SAMPLES, samples, format, W, H);
		}
		else
		{
		
			glRenderbufferStorage(GL_RENDERBUFFER, format, W, H);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}	

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, atachmentType, RenderBufferTarget(multisampled), id);
	}



	static bool IsDepthFomat(const FBTextureFormat& format)	
	{
		switch (format)
		{
			case FBTextureFormat::DEPTH24STENCIL8: return true;	
		}
		return false;

	}



	// close namespace

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FBProps& props)
		: m_TextProps(props), m_FboID(0)//, m_TextColor(0), m_RenderBuffer(0)
	{
		for (auto prop : m_TextProps.List.Collection)
		{
			if (!IsDepthFomat(prop.TextureFormat)) m_ColorListProps.emplace_back(prop.TextureFormat);
			else m_DepthBufferProp = prop.TextureFormat;
		}

		ColorDepthAttachment();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FboID);
		glDeleteTextures(m_Colors.size(), m_Colors.data());
		glDeleteRenderbuffers(1, &m_Depth);
	

		m_Colors.clear();
		m_Depth = 0;
	}
	void OpenGLFrameBuffer::Bind() const
	{
		// PINTA SOBRE EL FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_FboID);
		RenderDrawCall::SetWiewPort(0, 0, m_TextProps.W, m_TextProps.H);
		//glViewport(0, 0, m_TextProps.W, m_TextProps.H);

		
		
	}
	void OpenGLFrameBuffer::Unbind() const
	{
		// DEJA DE PINTAR SOBRE EL FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		

	}
	void OpenGLFrameBuffer::ActiveTexture(uint32_t idx) const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Colors[idx]);

	}
	void OpenGLFrameBuffer::Resize(uint32_t W, uint32_t H)
	{
		m_TextProps.W = W; 
		m_TextProps.H = H;
		ColorDepthAttachment();
	}
	int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIdx, int x, int y)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIdx);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}
	void OpenGLFrameBuffer::ColorDepthAttachment()
	{
		if (m_FboID)
		{
			glDeleteFramebuffers(1, &m_FboID);
			glDeleteTextures(m_Colors.size(), m_Colors.data());
			glDeleteRenderbuffers(1, &m_Depth);


			m_Colors.clear();
			m_Depth = 0;
		}
		// generar el FBO
		glGenFramebuffers(1, &m_FboID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FboID);

		bool isMultiSample = m_TextProps.Samples > 1;
		// generar textura color // COLLECTIONS
		if (m_ColorListProps.size())
		{	
			m_Colors.resize(m_ColorListProps.size());

			CreateColorTexture(m_Colors.data(), m_Colors.size());

			for (size_t i = 0; i <  m_ColorListProps.size(); ++i)
			{
				BindTexture(isMultiSample, m_Colors[i]);

				switch (m_ColorListProps[i].TextureFormat)
				{
				case FBTextureFormat::RGBA8:
					AttachTexture(m_Colors[i], m_TextProps.Samples, GL_RGBA8, GL_RGBA, m_TextProps.W, m_TextProps.H, i); break;
				
				case FBTextureFormat::REDINTEGER:
				{
					AttachTexture(m_Colors[i], m_TextProps.Samples, GL_R32I, GL_RED_INTEGER, m_TextProps.W, m_TextProps.H, i); break;
				}
					
				}
			}
		}

		

		if (m_DepthBufferProp.TextureFormat != FBTextureFormat::NONE)
		{
			
			CreateRenderBuffer(&m_Depth, 1);
			BinRenderBuffer(isMultiSample, m_Depth);

			switch (m_DepthBufferProp.TextureFormat)
			{
			case FBTextureFormat::DEPTHCOMPONENT24:
				AttachRenderBuffer(m_Depth, isMultiSample, GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT, m_TextProps.W, m_TextProps.H); break;
			//case FBTextureFormat::DEPTH24STENCIL8:
				//AttachTexture(m_Depth, m_TextProps.Samples, GL_DEPTH24_STENCIL8, m_TextProps.W, m_TextProps.H); break;
			}
		}

		if (m_Colors.size() > 1 && m_Colors.size() < 5)
		{			
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_Colors.size(), buffers);
			
		}


		//glGenTextures(1, &m_TextColor);
		//glBindTexture(GL_TEXTURE_2D, m_TextColor);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TextProps.W, m_TextProps.H, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glBindTexture(GL_TEXTURE_2D, 0);

		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextColor, 0);




		//// DEPTH -> usamos la misma textura para el buffer de profundidad hasta mejor idea
		//glGenRenderbuffers(1, &m_RenderBuffer);
		//glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer); 
		//
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_TextProps.W, m_TextProps.H);
		//glBindRenderbuffer(GL_RENDERBUFFER, 0);

		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);





		CheckFrameBufferStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);		

		
	}
}