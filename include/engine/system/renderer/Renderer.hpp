#pragma once

namespace MHelmet
{
	enum class RendererAPI
	{
		None = 0, 
		OpenGL, 
		DirectX, 
		Vulkan
	};

	class Renderer
	{
	public:
		static RendererAPI GetAPI();
	private:
		static RendererAPI s_API;
	};

	
}