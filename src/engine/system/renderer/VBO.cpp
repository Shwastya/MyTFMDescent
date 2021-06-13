#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/renderer/VBO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVBO.hpp" 

namespace MHelmet
{
	VBO* VBO::Create(float* vertices, uint32_t size)
	{

		//return new OpenGLVBO(vertices, size);

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:

			return new OpenGLVBO(vertices, size);
		
	
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