#include "engine/system/platform/RenderAPI/OpenGL/OpenGLFrameBuffer.hpp"
#include "engine/system/renderer/Framebuffer.hpp"
#include "engine/system/renderer/Renderer.hpp"

namespace MHelmet
{
	RefCount<FrameBuffer> FrameBuffer::Create(const FBProps& textureProps)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				break;
			case RendererAPI::API::OpenGL: 

				return std::make_shared<OpenGLFrameBuffer>(textureProps);
				break;
			case RendererAPI::API::DirectX:
			
				break;
			case RendererAPI::API::Vulkan:	
			default:
				// MENSAJE DE ERROR (API desconocida)
				return nullptr;
				break;
		}
	}
}