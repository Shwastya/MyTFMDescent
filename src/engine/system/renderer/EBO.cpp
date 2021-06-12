#include "engine/system/renderer/EBO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp"

#include "engine/system/renderer/Renderer.hpp"

namespace MHelmet
{
	std::shared_ptr<EBO> EBO::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::OpenGL:
			
			return std::make_shared<OpenGLEBO>(indices, size);

			break;
		case RendererAPI::DirectX:
			// NADA DE MOMENTO
			break;
		case RendererAPI::Vulkan:
			// CON Vulkan PODEMOS FLIPAR
			break;
		default:
			// MENSAJE DE ERRAR (API desconocida)
			return nullptr;
			break;
		}
	}
}