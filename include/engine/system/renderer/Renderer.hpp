#pragma once
#include "engine/system/renderer/RenderCommand.hpp"
#include "PerspectiveCamera.hpp"
#include "engine/system/shader.hpp"

namespace MHelmet
{	
	class Renderer
	{
	public:

		static void BeginScene(std::shared_ptr<PerspectiveCamera>& camera);
		static void EndEscene();

		static void Submit(const std::shared_ptr<Shader>& _Shader, const std::shared_ptr<VAO>& _VAO);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct DataScene
		{
			glm::mat4 Projection;
			glm::mat4 Model;
			glm::mat4 View;

			glm::mat4 ViewMatrixRefresh;
		};

		static DataScene* Scene;
		static PerspectiveCamera* camera;
	};

	
}