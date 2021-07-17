#pragma once
#include "engine/system/renderer/RenderDrawCall.hpp"
#include "engine/system/renderer/Texture.hpp"
#include "PerspectiveCamera.hpp"


#define SHADER   std::reinterpret_pointer_cast<OpenGLShader>
#define W_WIDTH  static_cast<float>(Engine::p().GetWindow().GetWidth())
#define W_HEIGHT static_cast<float>(Engine::p().GetWindow().GetHeight())

namespace MHelmet
{	
	class Renderer
	{
	public:
		static void Init();
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); } 
	};

}