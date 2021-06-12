#include "engine/system/renderer/VBO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVBO.hpp"

#include "engine/system/renderer/Renderer.hpp"

namespace MHelmet
{
	std::shared_ptr<VBO> VBO::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::OpenGL:
			//return new OpenGLVBO(vertices, size);
			return std::make_shared<OpenGLVBO>(vertices, size);
			break;
		case RendererAPI::DirectX:
			// NADA DE MOMENTO
			break;
		case RendererAPI::Vulkan:
			// CON Vulkan PODEMOS FLIPAR
			break;
		default:
			// MENSAJE DE ERROR (API desconocida)
			return nullptr;
			break;
		}
	}
}