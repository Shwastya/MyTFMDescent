#pragma once
//#include "engine/system/renderer/RenderCommand.hpp"
#include <glm/glm.hpp>
#include "engine/system/renderer/VAO.hpp"

namespace MHelmet
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DirectX = 2, Vulkan = 3
		};

	public:

		

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VAO>& _VAO) = 0;

		inline static API GetAPI() { return s_API; }

		static void SetAPI(RendererAPI::API rendererAPI = RendererAPI::API::OpenGL);

	private:
		const static API s_API{ API::OpenGL };
		//static API s_API;
	};
}