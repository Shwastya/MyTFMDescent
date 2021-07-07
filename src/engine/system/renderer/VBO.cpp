#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/renderer/VBO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVBO.hpp" 

namespace MHelmet
{
	std::shared_ptr<VBO> VBO::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: // MENSAJE DE ERROR(NOT SUPPORTED)
				
			case RendererAPI::API::OpenGL:

				return std::make_shared<OpenGLVBO>(vertices, size);		
	
			case RendererAPI::API::DirectX:  // Devolveria DirectX			
		
			case RendererAPI::API::Vulkan:   // Devolveria Vulkan			
		
			default: return nullptr; // MENSAJE DE ERROR (API desconocida)						
		}
	}
}