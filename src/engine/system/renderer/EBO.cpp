#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/renderer/EBO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp"



namespace MHelmet
{
	EBO* EBO::Create(uint32_t* indices, uint32_t size)
	{
		//return new OpenGLEBO(indices, size);

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:
			
			return new OpenGLEBO(indices, size);

		case RendererAPI::API::DirectX:
			// NADA DE MOMENTO
			break;
		case RendererAPI::API::Vulkan:
			// CON Vulkan PODEMOS FLIPAR
			break;
		default:
			// MENSAJE DE ERRAR (API desconocida)
			return nullptr;
			break;
		}
	}
}