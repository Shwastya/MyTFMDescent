//#include "engine/system/renderer/RendererAPI.hpp"
#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/renderer/VAO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVAO.hpp"



namespace MHelmet
{
	
	RefCount<VAO> VAO::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:

			//return new OpenGLVAO();
			return std::make_shared<OpenGLVAO>();
			
		case RendererAPI::API::DirectX:
			// NADA DE MOMENTO
			break;
		case RendererAPI::API::Vulkan:
			// JUAS
			break;
		default:
			// MENSAJE DE ERROR (API desconocida)
			return nullptr;
			break;
		}
	}
	
}