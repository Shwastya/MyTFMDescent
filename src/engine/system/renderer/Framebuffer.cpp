#include "engine/system/platform/RenderAPI/OpenGL/OpenGLFrameBuffer.hpp"
#include "engine/system/renderer/Framebuffer.hpp"
#include "engine/system/renderer/Renderer.hpp"

namespace MHelmet
{
	RefCount<FrameBuffer> FrameBuffer::Create(const FBTextureProps& props)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:

			//return new OpenGLVBO(vertices, size);
			return std::make_shared<OpenGLVBO>(vertices, size);


		case RendererAPI::API::DirectX:
			// NADA DE MOMENTO
			break;
		case RendererAPI::API::Vulkan:
			// CON Vulkan PODEMOS FLIPAR
			break;
		default:
			// MENSAJE DE ERROR (API desconocida)
			return nullptr;
			break;
		}
	}
}







//#include "hzpch.h"
//#include "Framebuffer.h"
//
//#include "Hazel/Platform/OpenGL/OpenGLFramebuffer.h"
//#include "Hazel/Platform/Vulkan/VulkanFramebuffer.h"
//
//#include "Hazel/Renderer/RendererAPI.h"
//
//namespace Hazel {
//
//	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
//	{
//		Ref<Framebuffer> result = nullptr;
//
//		switch (RendererAPI::Current())
//		{
//			case RendererAPIType::None:		return nullptr;
//			case RendererAPIType::OpenGL:	result = Ref<OpenGLFramebuffer>::Create(spec); break;
//			case RendererAPIType::Vulkan:	result = Ref<VulkanFramebuffer>::Create(spec); break;
//		}
//		FramebufferPool::GetGlobal()->Add(result);
//		return result;
//	}
//
//	FramebufferPool* FramebufferPool::s_Instance = new FramebufferPool;
//
//	FramebufferPool::FramebufferPool(uint32_t maxFBs /* = 32 */)
//	{
//	}
//
//	FramebufferPool::~FramebufferPool()
//	{
//		
//	}
//
//	std::weak_ptr<Framebuffer> FramebufferPool::AllocateBuffer()
//	{
//		// m_Pool.push_back();
//		return std::weak_ptr<Framebuffer>();
//	}
//
//	void FramebufferPool::Add(const Ref<Framebuffer>& framebuffer)
//	{
//		m_Pool.push_back(framebuffer);
//	}
//
//}