#pragma once

#include "engine/system/renderer/RendererApi.hpp"

namespace MHelmet
{
	// RenderCommand tiene un puntero al rendererAPI
	class RenderCommand
	{
	public:

		inline static 
		void SetClearColor(const glm::vec4& color) 
		{
			s_RenderererAPI->SetClearColor(color);
		}
		
		inline static 
		void clear()
		{
			s_RenderererAPI->clear();
		}

		inline static
		void DrawIndexed(const std::shared_ptr<VAO>& _VAO)
		{
			s_RenderererAPI->DrawIndexed(_VAO);
		}

	private:

		static RendererAPI* s_RenderererAPI;
	};
}