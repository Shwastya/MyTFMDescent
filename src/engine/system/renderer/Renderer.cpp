#include "engine/system/renderer/Renderer.hpp"


namespace MHelmet
{
	RendererAPI Renderer::s_API = RendererAPI::OpenGL;

	RendererAPI Renderer::GetAPI() 
	{
		return s_API;
	}
}