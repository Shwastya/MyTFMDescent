//#include "../src/engine/mhpch.cpp"
#include "engine/system/renderer/Texture.hpp"
//#include "engine/shader.hpp"
//#include "../src/engine/mhpch.cpp"

#include <glad/glad.h>


#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLTexture.hpp"

namespace MHelmet
{
	RefCount<Texture2D> Texture2D::Create(const std::string& path, Texture2D::Format format)
	{
		return std::make_shared<OpenGLTexture2D>(path, format);
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:

		//	return std::make_shared<OpenGLTexture2D>(path, format);
			//return std::make_shared<OpenGLVAO>();

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