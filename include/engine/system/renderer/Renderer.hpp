#pragma once
#include "engine/system/renderer/RenderCommand.hpp"

namespace MHelmet
{	
	class Renderer
	{
	public:

		static void BeginScene();
		static void EndEscene();

		static void Submit(const std::shared_ptr<VAO>& _VAO);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
	};

	
}