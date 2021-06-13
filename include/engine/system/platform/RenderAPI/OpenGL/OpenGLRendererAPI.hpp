#include "engine/system/MHCore.hpp"

#include "engine/system/renderer/RendererApi.hpp"

namespace MHelmet
{
	class OpenGlRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VAO>& _VAO);

	

	};
}