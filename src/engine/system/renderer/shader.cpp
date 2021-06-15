#include "../src/engine/mhpch.cpp"
//#include "engine/system/renderer/shader.hpp"

#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"

//#include <glad/glad.h>
//#include <glm/gtc/type_ptr.hpp>


#include <sstream>

namespace MHelmet
{
	std::shared_ptr<Shader> Shader::create(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{

		//return new OpenGLVBO(vertices, size);

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			// PONER MENSAJE DE ERROR (NOT SUPPORTED)
			break;
		case RendererAPI::API::OpenGL:

			return std::make_shared<OpenGLShader>(vertexPath, fragmentPath, geometryPath);


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

