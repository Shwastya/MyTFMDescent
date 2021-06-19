#include "../src/engine/mhpch.cpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include <sstream>

namespace MHelmet
{
	RefCount<Shader>Shader::Create(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:

			return std::make_shared<OpenGLShader>(name, vertexPath, fragmentPath, geometryPath);

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

	RefCount<Shader>Shader::Create(const std::string& name, const std::string& GLSLFilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:

			return std::make_shared<OpenGLShader>(name, GLSLFilePath);

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