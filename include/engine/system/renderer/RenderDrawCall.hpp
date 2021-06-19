#pragma once


#include "engine/system/renderer/RendererApi.hpp"

namespace MHelmet
{
	// RenderCommand tiene un puntero al rendererAPI
	class RenderDrawCall
	{
	public:

		inline static void Init()
		{
			s_RenderererAPI->Init();
		}

		static void ClearColor(const glm::vec4& color) { s_RenderererAPI->ClearColor(color); }
		
		static void clear()	{ s_RenderererAPI->clear();	}

		static void SetWiewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h) 
		{
			s_RenderererAPI->SetViewPort(x, y, w, h);
		};

		static void Draw(const RefCount<VAO>& _VAO) { s_RenderererAPI->Draw(_VAO); }

		

	private:

		static RendererAPI* s_RenderererAPI;
	};
}