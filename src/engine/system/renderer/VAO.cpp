#include "engine/system/renderer/VAO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVAO.hpp"

#include "engine/system/renderer/Renderer.hpp"

namespace MHelmet
{
	
	std::unique_ptr<VAO> VAO::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::OpenGL:
			//return new OpenGLVBO(vertices, size);
			return std::make_unique<OpenGLVAO>();
			break;
		case RendererAPI::DirectX:
			// NADA DE MOMENTO
			break;
		case RendererAPI::Vulkan:
			// JUAS
			break;
		default:
			// MENSAJE DE ERROR (API desconocida)
			return nullptr;
			break;
		}
	}
}